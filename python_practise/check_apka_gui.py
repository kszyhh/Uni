import tkinter as tk
import requests

def odswiez_dane():
    miasta = ["Krakow", "Tarnow", "Barcelona"]
    coiny = ['BTCUSDT', 'XMRUSDT', 'SOLUSDT']

    tekst_pogoda = "==============================\n"
    for miasto in miasta:
        url = f"https://wttr.in/{miasto}?format=j1"
        try:
            odpowiedz = requests.get(url, timeout=5)
            
            if odpowiedz.status_code == 200:
                dane = odpowiedz.json()
                temp = dane['current_condition'][0]['temp_C']
                
                # Bezpieczniejsze pobieranie opisu (unika błędu KeyError)
                opis = "Brak opisu"
                if 'lang_pl' in dane['current_condition'][0]:
                    opis = dane['current_condition'][0]['lang_pl'][0]['value']
                elif 'weatherDesc' in dane['current_condition'][0]:
                    opis = dane['current_condition'][0]['weatherDesc'][0]['value']

                tekst_pogoda += f"🌍 Pogoda w: {miasto}\n"
                tekst_pogoda += f"🌡️ Temperatura: {temp}°C\n"
                tekst_pogoda += f"☁️ Niebo: {opis}\n"
                tekst_pogoda += "------------------------------\n"
            else:
                tekst_pogoda += f"⚠️ {miasto}: Błąd serwera ({odpowiedz.status_code})\n------------------------------\n"
                
        except Exception as e:
            tekst_pogoda += f"❌ {miasto}: Błąd połączenia\n------------------------------\n"

    label_pogoda.config(text=tekst_pogoda)


    tekst_krypto = "==============================\nKURSY KRYPTO\n"
    for coin in coiny:
        url = f"https://api.mexc.com/api/v3/ticker/price?symbol={coin}"
        try:
            odpowiedz = requests.get(url, timeout=5)
            if odpowiedz.status_code == 200:
                dane = odpowiedz.json()
                kurs = float(dane['price']) 
                tekst_krypto += f"💰 {coin}: {kurs:.2f} USD\n"
            else:
                tekst_krypto += f"⚠️ {coin}: Błąd serwera\n"
        except Exception as e:
            tekst_krypto += f"❌ {coin}: Błąd połączenia\n"

    label_krypto.config(text=tekst_krypto)

    root.after(60000, odswiez_dane)


root = tk.Tk()
root.title("Moje Krypto i Pogoda")
root.geometry("550x700") 
root.configure(bg="#121212")

label_pogoda = tk.Label(root, text="Pobieranie pogody...", font=("Consolas", 12), bg="#121212", fg="white", justify="left")
label_pogoda.pack(pady=10)

label_krypto = tk.Label(root, text="Pobieranie krypto...", font=("Consolas", 12), bg="#121212", fg="#00ff00", justify="left")
label_krypto.pack(pady=10)

odswiez_dane()

root.mainloop()
