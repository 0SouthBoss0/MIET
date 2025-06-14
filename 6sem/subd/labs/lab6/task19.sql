-- Создаем временные таблицы перед началом блока
CREATE TEMP TABLE IF NOT EXISTS tournament_results (
    round INT,
    player_id INT,
    last_name VARCHAR(30),
    first_name VARCHAR(30),
    points INT DEFAULT 0,
    PRIMARY KEY (round, player_id)
);

CREATE TEMP TABLE IF NOT EXISTS game_history (
    round INT,
    player1_id INT,
    player1_last_name VARCHAR(30),
    player2_id INT,
    player2_last_name VARCHAR(30),
    result VARCHAR(50),
    PRIMARY KEY (round, player1_id, player2_id)
);

TRUNCATE TABLE tournament_results;
TRUNCATE TABLE game_history;

DO $$
DECLARE
    tournament_round INT := 1;
    current_players INT := 10;
    players_to_eliminate INT := 2;
    player1 RECORD;
    player2 RECORD;
    game_result INT;
    remaining_players INT[];
    all_players INT[];
    player_score INT;
    pos INT;
    game_rec RECORD;
    player_data RECORD;
BEGIN
    -- Выбираем 10 случайных студентов для участия в турнире
    INSERT INTO tournament_results (round, player_id, last_name, first_name, points)
    SELECT 
        1, 
        student_id, 
        last_name, 
        first_name, 
        0
    FROM public.students
    ORDER BY random()
    LIMIT 10;
    
    -- Получаем список всех игроков первого раунда
    SELECT array_agg(player_id) INTO all_players
    FROM tournament_results
    WHERE round = 1;
    
    -- Основной цикл турнира
    WHILE current_players > 2 LOOP
        RAISE NOTICE '--- Начало раунда % ---', tournament_round;
        
        -- Проводим игры между всеми участниками текущего раунда
        FOR i IN 1..array_length(all_players, 1) LOOP
            FOR j IN (i+1)..array_length(all_players, 1) LOOP
                -- Получаем данные игроков
                SELECT INTO player1 * FROM tournament_results 
                WHERE round = tournament_round AND player_id = all_players[i];
                
                SELECT INTO player2 * FROM tournament_results 
                WHERE round = tournament_round AND player_id = all_players[j];
                
                -- Определяем результат игры случайным образом
                game_result := floor(random() * 2); -- 0 - победа 1го, 1 - победа 2го
                
                -- Записываем результат игры в историю
                IF game_result = 0 THEN
                    INSERT INTO game_history VALUES (
                        tournament_round, 
                        player1.player_id, 
                        player1.last_name, 
                        player2.player_id, 
                        player2.last_name, 
                        'Победил ' || player1.last_name
                    );
                    
                    -- Обновляем очки
                    UPDATE tournament_results 
                    SET points = points + 2 
                    WHERE round = tournament_round AND player_id = player1.player_id;
                ELSE 
                    INSERT INTO game_history VALUES (
                        tournament_round, 
                        player1.player_id, 
                        player1.last_name, 
                        player2.player_id, 
                        player2.last_name, 
                        'Победил ' || player2.last_name
                    );
                    
                    UPDATE tournament_results 
                    SET points = points + 2 
                    WHERE round = tournament_round AND player_id = player2.player_id;   
                END IF;
            END LOOP;
        END LOOP;
        
        -- Выводим результаты игр текущего раунда
        RAISE NOTICE 'Результаты игр раунда %:', tournament_round;
        FOR game_rec IN SELECT * FROM game_history WHERE round = tournament_round ORDER BY player1_last_name, player2_last_name LOOP
            RAISE NOTICE '% vs %: %', 
                game_rec.player1_last_name, 
                game_rec.player2_last_name, 
                game_rec.result;
        END LOOP;
        
        -- Выводим таблицу результатов текущего раунда с правильным порядком при равных очках
        RAISE NOTICE 'Итоговая таблица раунда %:', tournament_round;
        RAISE NOTICE 'Место | Фамилия       | Имя          | Очки';
        RAISE NOTICE '------+---------------+--------------+------';
        
        pos := 1;
        FOR player_data IN 
            SELECT 
                last_name, 
                first_name, 
                points,
                rank() OVER (ORDER BY points DESC) as position
            FROM tournament_results 
            WHERE round = tournament_round 
            ORDER BY points DESC, last_name, first_name
        LOOP
            RAISE NOTICE '% | % | % | %', 
                lpad(player_data.position::text, 5), 
                rpad(player_data.last_name, 13), 
                rpad(player_data.first_name, 12), 
                player_data.points;
        END LOOP;
        
        -- Определяем игроков, которые выбывают
        players_to_eliminate := 2;
        
        -- Получаем список игроков для следующего раунда (исключаем худших)
        WITH eliminated AS (
            SELECT player_id 
            FROM tournament_results 
            WHERE round = tournament_round 
            ORDER BY points, last_name, first_name
            LIMIT players_to_eliminate
        )
        SELECT array_agg(player_id) INTO remaining_players
        FROM tournament_results
        WHERE round = tournament_round AND player_id NOT IN (SELECT player_id FROM eliminated);
        
        -- Уменьшаем количество текущих игроков
        current_players := current_players - players_to_eliminate;
        
        -- Если осталось больше 2 игроков, готовим следующий раунд
        IF current_players >= 2 THEN
            tournament_round := tournament_round + 1;
            
            -- Копируем оставшихся игроков в следующий раунд с нулевыми очками
            INSERT INTO tournament_results (round, player_id, last_name, first_name, points)
            SELECT 
                tournament_round, 
                tr.player_id, 
                tr.last_name, 
                tr.first_name, 
                0
            FROM tournament_results tr
            WHERE tr.round = tournament_round - 1 AND tr.player_id = ANY(remaining_players);
            
            -- Обновляем список игроков для следующего раунда
            all_players := remaining_players;
        END IF;
    END LOOP;
    
    -- Проводим финальный матч между последними двумя игроками
    IF current_players = 2 THEN
        tournament_round := tournament_round + 1;
        
        -- Копируем финалистов в новый раунд
        INSERT INTO tournament_results (round, player_id, last_name, first_name, points)
        SELECT 
            tournament_round, 
            tr.player_id, 
            tr.last_name, 
            tr.first_name, 
            0
        FROM tournament_results tr
        WHERE tr.round = tournament_round - 1
        ORDER BY tr.points DESC, tr.last_name, tr.first_name;
        
        -- Получаем данные финалистов
        SELECT INTO player1 * FROM tournament_results 
        WHERE round = tournament_round 
        ORDER BY player_id LIMIT 1;
        
        SELECT INTO player2 * FROM tournament_results 
        WHERE round = tournament_round 
        ORDER BY player_id DESC LIMIT 1;
        
        -- Проводим финальный матч
        game_result := floor(random() * 2);
        
        IF game_result = 0 THEN
            INSERT INTO game_history VALUES (
                tournament_round, 
                player1.player_id, 
                player1.last_name, 
                player2.player_id, 
                player2.last_name, 
                'ФИНАЛ: Победил ' || player1.last_name
            );
            
            UPDATE tournament_results 
            SET points = points + 2 
            WHERE round = tournament_round AND player_id = player1.player_id;
        ELSE 
            INSERT INTO game_history VALUES (
                tournament_round, 
                player1.player_id, 
                player1.last_name, 
                player2.player_id, 
                player2.last_name, 
                'ФИНАЛ: Победил ' || player2.last_name
            );
            
            UPDATE tournament_results 
            SET points = points + 2 
            WHERE round = tournament_round AND player_id = player2.player_id;
        END IF;
        
        -- Выводим результат финального матча
        RAISE NOTICE '--- ФИНАЛЬНЫЙ МАТЧ ---';
        IF game_result = 0 THEN
            RAISE NOTICE '% % vs % %: Победил %', 
                player1.first_name, player1.last_name,
                player2.first_name, player2.last_name,
                player1.last_name;
        ELSE
            RAISE NOTICE '% % vs % %: Победил %', 
                player1.first_name, player1.last_name,
                player2.first_name, player2.last_name,
                player2.last_name;
        END IF;
    END IF;
    
    -- Выводим финальную таблицу
    RAISE NOTICE '--- ФИНАЛЬНАЯ ТАБЛИЦА ---';
    RAISE NOTICE 'Место | Фамилия       | Имя          | Очки';
    RAISE NOTICE '------+---------------+--------------+------';
    
    pos := 1;
    FOR player_data IN 
        WITH final_results AS (
            SELECT 
                last_name, 
                first_name, 
                points,
                rank() OVER (ORDER BY points DESC) as position
            FROM tournament_results 
            WHERE round = tournament_round 
            ORDER BY points DESC, last_name, first_name
        )
        SELECT 
            position,
            last_name, 
            first_name, 
            points
        FROM final_results
    LOOP
        RAISE NOTICE '% | % | % | %', 
            lpad(player_data.position::text, 5), 
            rpad(player_data.last_name, 13), 
            rpad(player_data.first_name, 12), 
            player_data.points;
    END LOOP;
    
    -- Выводим победителя
    SELECT INTO player1 * FROM tournament_results 
    WHERE round = tournament_round 
    ORDER BY points DESC, last_name, first_name
    LIMIT 1;
    
    RAISE NOTICE 'ПОБЕДИТЕЛЬ ТУРНИРА: % %!', player1.first_name, player1.last_name;
END $$;