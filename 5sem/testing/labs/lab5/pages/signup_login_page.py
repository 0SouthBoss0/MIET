from selenium.webdriver.common.by import By


class SignUpLoginPage:
    def __init__(self, driver):
        self.driver = driver
        self.name_input = self.driver.find_element(By.XPATH, "//input[contains(@data-qa,'signup-name')]")
        self.email_input = self.driver.find_element(By.XPATH, "//input[contains(@data-qa,'signup-email')]")
        self.register_button = self.driver.find_element(By.XPATH, "//button[contains(@data-qa,'signup-button')]")