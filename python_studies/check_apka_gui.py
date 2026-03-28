import tkinter as tk
import requests


def odswiez_dane():
    miasta = ["Krakow", "Tarnow", "Barcelona"]
    coiny = ['BTCUSDT', 'XMRUSDT', 'SOLUSDT']

    for miasto in miasta:
        url = f"https://wttr.in/{miasto}?format=j1"
        odpowiedz = requests.get(url)

        if odpowiedz.status_code == 200:
            dane = odpowiedz.json()
            temp = dane['current_condition'][0]['temp_C']
            opis = dane['current_condition'][0]['lang_pl'][0]['value'] if 'lang_pl' in dane[
                'current_condition'][0] else dane['current_condition'][0]['weatherDesc'][0]['value']

            tekst_pogoda = "==============================\n"
            tekst_pogoda += f"🌍 Pogoda w: {miasto}\n"
            tekst_pogoda += f"🌡️ Temperatura: {temp}°C\n"
            tekst_pogoda += f"☁️ Niebo: {opis}\n"
        else:
            tekst_pogoda += "Błąd! Nie udało się pobrać danych.\n"

    label_pogoda.config(text=tekst_pogoda)

    tekst_krypto = "==============================\nKURSY\n"
    for coin in coiny:
        url = f"https://api.mexc.com/api/v3/ticker/price?symbol={coin}"
        odpowiedz = requests.get(url)
        if odpowiedz.status_code == 200:
            dane = odpowiedz.json()
            kurs = dane['price']
            tekst_krypto += f"{coin}: {kurs} USD\n"
        else:
            tekst_krypto += "błąd\n"

    label_krypto.config(text=tekst_krypto)

    root.after(60000, odswiez_dane)


root = tk.Tk()
root.title("Moje Krypto i Pogoda")
root.geometry("350x550")
root.configure(bg="#121212")

label_pogoda = tk.Label(root, text="Pobieranie...", font=(
    "Consolas", 12), bg="#121212", fg="white", justify="left")
label_pogoda.pack(pady=10)

label_krypto = tk.Label(root, text="", font=(
    "Consolas", 12), bg="#121212", fg="#00ff00", justify="left")
label_krypto.pack(pady=10)

odswiez_dane()

root.mainloop()
