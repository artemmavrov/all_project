import requests
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry

def get(url, params={}, timeout=5, max_retries=5, backoff_factor=0.3):
    retries = Retry(total=max_retries, backoff_factor=backoff_factor)
    session = requests.Session()
    session.mount('http://', HTTPAdapter(max_retries=retries))
    session.mount('https://', HTTPAdapter(max_retries=retries))
    
    try:
        response = session.get(url, timeout=(timeout, timeout), stream=True, params=params)
        response.raise_for_status()
        return response.json()
    except requests.exceptions.RequestException as e:
        return e