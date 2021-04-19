import urllib.request, json
import datetime

class Rate(object):
    def __init__(self, diff):
        self.diff = diff
        with urllib.request.urlopen("https://www.cbr-xml-daily.ru/daily_json.js") as url:
            self.data = json.loads(url.read().decode())
        
    def print_rate(self, name):
        name = name.upper()
        if(self.diff):
            print('Разница между предыдушим курсом валюты ' + '"'+ self.data["Valute"][name]["Name"] +'" равна: ' + str(round(self.data["Valute"][name]["Value"] - self.data["Valute"][name]["Previous"], 2)))
        else:
            print('Действительный курс валюты ' + '"'+ self.data["Valute"][name]["Name"] +'" равна: ' + str(self.data["Valute"][name]["Value"]))
            

    def max_money(self):
        value_max = 0;
        name_valute = ''
        for i in self.data["Valute"]:
            if(self.data["Valute"][i]["Value"] > value_max):
                value_max = self.data["Valute"][i]["Value"]
                name_valute = i
        self.name = self.data["Valute"][name_valute]["Name"]

test_rate = Rate(True)
test_rate.max_money()
print(test_rate.name)
test_rate.print_rate('aud')
