from selenium.webdriver.common.by import By


class MainPage:
    def __init__(self, driver):
        self.driver = driver
        self.signup_button = self.driver.find_element(By.XPATH, "//a[@href='/login']")
