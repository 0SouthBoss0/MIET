from selenium.webdriver.common.by import By
from selenium.webdriver.support.select import Select


class SignUpPage:
    def __init__(self, driver):
        self.driver = driver
        self.title_mr = self.driver.find_element(By.ID, "id_gender1")
        self.title_mrs = self.driver.find_element(By.ID, "id_gender2")
        self.name_field = self.driver.find_element(By.ID, "name")
        self.email_field = self.driver.find_element(By.ID, "email")
        self.password_field = self.driver.find_element(By.ID, "password")
        self.birth_day = self.driver.find_element(By.ID, "days")
        self.birth_month = self.driver.find_element(By.ID, "months")
        self.birth_year = self.driver.find_element(By.ID, "years")
        self.newsletter = self.driver.find_element(By.ID, "newsletter")
        self.offers = self.driver.find_element(By.ID, "optin")
        self.first_name = self.driver.find_element(By.ID, "first_name")
        self.last_name = self.driver.find_element(By.ID, "last_name")
        self.company = self.driver.find_element(By.ID, "company")
        self.address1 = self.driver.find_element(By.ID, "address1")
        self.address2 = self.driver.find_element(By.ID, "address2")
        self.country = Select(self.driver.find_element(By.ID, "country"))
        self.state = self.driver.find_element(By.ID, "state")
        self.city = self.driver.find_element(By.ID, "city")
        self.zipcode = self.driver.find_element(By.ID, "zipcode")
        self.number = self.driver.find_element(By.ID, "mobile_number")
        self.submit_button = self.driver.find_element(By.XPATH, "//button[contains(@data-qa,'create-account')]")

