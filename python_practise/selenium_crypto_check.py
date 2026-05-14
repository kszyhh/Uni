from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.options import Options
import time
from datetime import datetime




options = Options()
options.add_argument('--headless') #working in the background
driver = webdriver.Firefox(options=options)
#driver.get("https://www.google.com/finance/beta/quote/BTC-USD")

cryptos = ['BTC','SOL','XMR']

while (True):
    
    try:
        for i in cryptos:
            now = datetime.now()
            driver.get(f"\nhttps://www.google.com/finance/beta/quote/{i}-USD")    
            name = driver.find_element(By.CLASS_NAME,'gO24Ff')
            price = driver.find_element(By.CLASS_NAME,'N6SYTe')
            print(now.strftime("%Y-%m-%d %H:%M"), f"{name.text} {price.text}\n")
        print("=" * 50)
        time.sleep(30)
        driver.refresh()
            

    except Exception as e:
        print("An error has occured while downloading the data at ", datetime.now() , e)
        time.sleep(30)
        driver.refresh()
    

#driver.quit()