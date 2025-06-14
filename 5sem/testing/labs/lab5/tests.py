import unittest

from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.select import Select
from selenium.webdriver.support.wait import WebDriverWait
from selenium.webdriver.chrome.options import Options

from pages.account_deleted_page import AccountDeletedPage
from pages.main_page import MainPage
from pages.signup_login_page import SignUpLoginPage
from pages.signup_page import SignUpPage
from pages.account_created_page import AccountCreatedPage


# https://github.com/fabioarmandom/AutomationExercise

class RegisterDemo(unittest.TestCase):
    def setUp(self):
        options = Options()
        options.page_load_strategy = 'eager'
        self.driver = webdriver.Chrome(options=options)
        self.driver.get('https://automationexercise.com')
        self.driver.maximize_window()

    def test_login(self):
        main_page = MainPage(self.driver)
        self.assertEqual(self.driver.title, "Automation Exercise")
        main_page.signup_button.click()

        signup_login_page = SignUpLoginPage(self.driver)
        self.assertEqual(self.driver.title, "Automation Exercise - Signup / Login")
        self.assertTrue(self.driver.find_element(By.XPATH, "//*[contains(.,'New User Signup!')]"))
        signup_login_page.name_input.send_keys("my_name")
        signup_login_page.email_input.send_keys("my_email@myemail.com")
        signup_login_page.register_button.click()

        signup_page = SignUpPage(self.driver)
        self.assertEqual(self.driver.title, "Automation Exercise - Signup")
        self.assertTrue(self.driver.find_element(By.XPATH, "//*[contains(.,'Enter Account Information')]"))
        signup_page.title_mr.click()
        signup_page.password_field.send_keys("12345678")
        signup_page.birth_day.send_keys("26")
        signup_page.birth_month.send_keys("July")
        signup_page.birth_year.send_keys("1967")
        signup_page.newsletter.click()
        signup_page.offers.click()
        signup_page.first_name.send_keys("Jason")
        signup_page.last_name.send_keys("Statham")
        signup_page.company.send_keys("Hollywood")
        signup_page.address1.send_keys("Baker street")
        signup_page.country.select_by_visible_text("United States")
        signup_page.state.send_keys("State California")
        signup_page.city.send_keys("California")
        signup_page.zipcode.send_keys("888777")
        signup_page.number.send_keys("88000000000")
        signup_page.submit_button.click()

        account_created_page = AccountCreatedPage(self.driver)
        self.assertTrue(self.driver.find_element(By.XPATH, "//*[contains(.,'Account Created!')]"))
        account_created_page.continue_button.click()

        self.assertTrue(self.driver.find_element(By.XPATH, "//*[contains(.,'Logged in as my_name')]"))
        main_page.delete_account = self.driver.find_element(By.XPATH, "//a[@href='/delete_account']")
        main_page.delete_account.click()

        account_deleted_page = AccountDeletedPage(self.driver)
        self.assertTrue(self.driver.find_element(By.XPATH, "//*[contains(.,'Account Deleted!')]"))
        account_deleted_page.continue_button.click()

        self.assertEqual(self.driver.title, "Automation Exercise")
        self.assertEqual(self.driver.current_url, "https://automationexercise.com/")

    def tearDown(self):
        self.driver.quit()
