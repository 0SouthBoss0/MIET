from selenium.webdriver.common.by import By


class AccountCreatedPage:
    def __init__(self, driver):
        self.driver = driver
        self.continue_button = self.driver.find_element(By.XPATH, "//a[@data-qa='continue-button']")

