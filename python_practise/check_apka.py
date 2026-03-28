import requests
import os
import time

while True:
    os.system('clear')

    miasta = ["Krakow","Tarnow","Barcelona"] 
    coiny = ['BTCUSDT','XMRUSDT','SOLUSDT']

    for miasto in miasta:
        url = f"https://wttr.in/{miasto}?format=j1"

        odpowiedz = requests.get(url)

        if odpowiedz.status_code == 200:
            dane = odpowiedz.json()
            temp = dane['current_condition'][0]['temp_C']
            opis = dane['current_condition'][0]['lang_pl'][0]['value'] if 'lang_pl' in dane['current_condition'][0] else dane['current_condition'][0]['weatherDesc'][0]['value']
        
            print("==============================")
            print(f"🌍 Pogoda w: {miasto}")
            print(f"🌡️ Temperatura: {temp}°C")
            print(f"☁️ Niebo: {opis}")
        # print("==============================")
            


        else:
            print("Błąd! Nie udało się pobrać danych.")

    print("==============================")
    print("KURSY")
    for coin in coiny:
        url = f"https://api.mexc.com/api/v3/ticker/price?symbol={coin}"
        odpowiedz = requests.get(url)
        if odpowiedz.status_code == 200:
            dane = odpowiedz.json()
            kurs = dane['price']
            print(f"{coin}: {kurs} USD")
        else:
            print("błąd")
    time.sleep(60)
       



   
