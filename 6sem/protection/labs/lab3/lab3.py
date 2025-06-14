def hide_data(input_bmp, output_bmp, secret_file, end_marker=bytes([0xAB, 0xCD, 0xEF])):
    with open(secret_file, 'rb') as f:
        secret_data = f.read()
    with open(input_bmp, 'rb') as f:
        bmp_data = bytearray(f.read())

    # Проверка на BMP
    if bmp_data[0] != 0x42 or bmp_data[1] != 0x4D:
        print("Ошибка: Это не BMP файл!")
        return

    # Смещение до пикселей (little-endian)
    offset = bmp_data[10] | (bmp_data[11] << 8) | (bmp_data[12] << 16) | (bmp_data[13] << 24)

    # Проверка размера (учитываем сигнатуру конца)
    max_hide_size = (len(bmp_data) - offset) // 4
    if len(secret_data) + len(end_marker) > max_hide_size:
        print(f"Ошибка: Файл слишком большой. Максимум: {max_hide_size - len(end_marker)} байт")
        return

    # Добавляем сигнатуру конца
    secret_data += end_marker

    # Скрываем данные
    for i in range(len(secret_data)):
        byte = secret_data[i]
        pos = offset + i * 4

        # Записываем по 2 бита в каждый канал (B, G, R, Reserved)
        bmp_data[pos] = (bmp_data[pos] & 0xFC) | ((byte >> 6) & 0x03)
        bmp_data[pos + 1] = (bmp_data[pos + 1] & 0xFC) | ((byte >> 4) & 0x03)
        bmp_data[pos + 2] = (bmp_data[pos + 2] & 0xFC) | ((byte >> 2) & 0x03)
        bmp_data[pos + 3] = (bmp_data[pos + 3] & 0xFC) | (byte & 0x03)

    # Сохраняем BMP
    with open(output_bmp, 'wb') as f:
        f.write(bmp_data)
    print(f"Данные скрыты в {output_bmp}")


def extract_data(input_bmp, output_file, end_marker=bytes([0xAB, 0xCD, 0xEF])):
    with open(input_bmp, 'rb') as f:
        bmp_data = f.read()

    if bmp_data[0] != 0x42 or bmp_data[1] != 0x4D:
        print("Ошибка: Это не BMP файл!")
        return

    offset = bmp_data[10] | (bmp_data[11] << 8) | (bmp_data[12] << 16) | (bmp_data[13] << 24)
    result = bytearray()
    marker_pos = 0  # Текущая позиция в сигнатуре конца
    i = 0

    while True:
        pos = offset + i * 4
        if pos + 3 >= len(bmp_data):
            break  # Достигнут конец файла

        # Собираем байт из 4 каналов
        byte = (
                ((bmp_data[pos] & 0x03) << 6) |
                ((bmp_data[pos + 1] & 0x03) << 4) |
                ((bmp_data[pos + 2] & 0x03) << 2) |
                (bmp_data[pos + 3] & 0x03)
        )

        # Проверяем, совпадает ли текущий байт с ожидаемым в сигнатуре
        if byte == end_marker[marker_pos]:
            marker_pos += 1
            if marker_pos == len(end_marker):
                break  # Вся сигнатура найдена
        else:
            # Если последовательность нарушена, сбрасываем счётчик
            if marker_pos > 0:
                result.extend(end_marker[:marker_pos])  # Возвращаем "ложные" совпадения
                marker_pos = 0

            result.append(byte)
        i += 1

    # Сохраняем извлечённые данные (без сигнатуры конца)
    with open(output_file, 'wb') as f:
        f.write(result)
    print(f"Данные извлечены в {output_file}")


input_bmp = "lab3_variants/8.bmp"
output_file = "sample.txt"
extract_data(input_bmp, output_file, end_marker=bytes([0xFF]))

input_bmp = "lab3_variants/8.bmp"
output_bmp = "lab3_variants/8_secret.bmp"
secret_file = "docfile.doc"
hide_data(input_bmp, output_bmp, secret_file)

input_bmp = "lab3_variants/8_secret.bmp"
output_file = "docfile_NEW.doc"
extract_data(input_bmp, output_file)
