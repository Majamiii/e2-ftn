import requests
from bs4 import BeautifulSoup
from urllib.parse import urljoin
import os

URL = "https://www.acs.uns.ac.rs/sr/node/237/287"

os.makedirs("acs_fajlovi", exist_ok=True)

r = requests.get(URL, timeout=20)
soup = BeautifulSoup(r.text, "html.parser")

links = []
for a in soup.find_all("a", href=True):
    href = urljoin(URL, a["href"])
    if "/filebrowser/download/" in href:
        name = a.text.strip()
        links.append((name, href))

print(f"Pronađeno {len(links)} fajlova")

for name, link in links:
    path = os.path.join("acs_fajlovi", name)
    print("Skidam:", name)
    r = requests.get(link, timeout=60)
    with open(path, "wb") as f:
        f.write(r.content)

print("Gotovo.")