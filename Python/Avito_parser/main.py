import requests
from bs4 import BeautifulSoup
import csv

def get_html(url):
    proxies = {'http': "socks5://99.109.24.9:1080"}
    r = requests.get(url=url, proxies=proxies)
    return r.text

def get_total_pages(html):
    soup = BeautifulSoup(html, 'lxml')
    print(soup.find('p', class_='text').text)
    pages = soup.find('div', attrs={"data-marker" : "pagination-button"}).find_all('span')[-2].text
    return int(pages)

def write_csv(data):
    print(end)
    with open('avito.csv', 'a') as f:
        writer = csv.writer(f)

        writer.writerow( (data['title'],
                         data['price'],
                         data['metro'],
                         data['photo'],
                         data['url']) )
    

def get_page_data(html):
    soup = BeautifulSoup(html, 'lxml')

    ads = soup.find('div', class_='snippet-list').find_all('div', class_='item_table')

    for ad in ads:
        try:
            title = ad.find('a', class_="snippet-link").text
        except:
            title = "Загаловок пустой"
        try:
            url = 'https://www.avito.ru' + ad.find('a', class_="snippet-link").get('href')
        except:
            url = "Нет ссылки"
        try:
            price = ad.find('div', class_="snippet-price-row").find('span', class_="snippet-price").text.strip()
        except:
            price = "Нет цены"
        try:
            metro = ad.find('div', class_="snippet-date-row").find('div', class_="snippet-date-info").text.strip()
        except:
            metro = "Неизвестная дата"
        try:
            photo = soup_in.find('div', class_='item-photo').find('img').get('src')
        except:
            photo = "Нет фото"

        data = {'title' : title,
                'price' : price,
                'metro' : metro,
                'photo' : photo,
                'url' : url}

        write_csv(data)
        

def main():
    base_url = "https://www.avito.ru/rossiya/muzykalnye_instrumenty/dlya_studii_i_kontsertov-ASgBAgICAUTEAsgK?d=1&pmax=5000&q=dj+контроллер&p=1"

    total_pages = get_total_pages(get_html(base_url))
    
    for i in range(1, total_pages + 1):
        url_gen = base_url[:-1] + str(i)
        html = get_html(url_gen)
        get_page_data(html)


if __name__ == '__main__':
    main()
