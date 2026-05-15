import pytest
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.options import Options
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.firefox.service import Service

@pytest.fixture
def przegladarka():
    PATH = "/home/kszyh/Desktop/coding/python_practise.org/geckodriver"
    service = Service(PATH)
    options = Options()
    options.add_argument("--headless") 
    driver = webdriver.Firefox(service=service,options=options)
    yield driver
    driver.quit()


def test_logowanie_zly_login(przegladarka):
    przegladarka.get("https://the-internet.herokuapp.com/login")
    
    przegladarka.find_element(By.ID, "username").send_keys("jakis_falszywy_login")
    przegladarka.find_element(By.ID, "password").send_keys("SuperSecretPassword!")
    przegladarka.find_element(By.CSS_SELECTOR, "button[type='submit']").click()
    
    pasek_bledu = WebDriverWait(przegladarka, 5).until(
        EC.presence_of_element_located((By.ID, "flash"))
    )
    
    assert "Your username is invalid!" in pasek_bledu.text


def test_logowanie_zle_haslo(przegladarka):
    przegladarka.get("https://the-internet.herokuapp.com/login")
    
    przegladarka.find_element(By.ID, "username").send_keys("tomsmith")
    przegladarka.find_element(By.ID, "password").send_keys("ZleHaslo123")
    przegladarka.find_element(By.CSS_SELECTOR, "button[type='submit']").click()
    
    pasek_bledu = WebDriverWait(przegladarka, 5).until(
        EC.presence_of_element_located((By.ID, "flash"))
    )
    
    assert "Your password is invalid!" in pasek_bledu.text


def test_logowanie_poprawne_dane(przegladarka):
    przegladarka.get("https://the-internet.herokuapp.com/login")
    
    przegladarka.find_element(By.ID, "username").send_keys("tomsmith")
    przegladarka.find_element(By.ID, "password").send_keys("SuperSecretPassword!")
    przegladarka.find_element(By.CSS_SELECTOR, "button[type='submit']").click()
    
    pasek_sukcesu = WebDriverWait(przegladarka, 5).until(
        EC.presence_of_element_located((By.ID, "flash"))
    )
    
    assert "You logged into a secure area!" in pasek_sukcesu.text