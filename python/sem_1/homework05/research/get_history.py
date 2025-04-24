import count_dates
import plotly
import chart_studio
import plotly.graph_objs as go
from count_dates import count_dates_from_messages
from func_get import get
from pprint import pprint as pp
import requests


def messages_get_history(user_id, offset=0, count=20):
    assert isinstance(user_id, int), "user_id must be positive integer"
    assert user_id > 0, "user_id must be positive integer"
    assert isinstance(offset, int), "offset must be positive integer"
    assert offset >= 0, "user_id must be positive integer"
    assert count >= 0, "user_id must be positive integer"
    # api key сообщества
    access_token = "vk1.a.fqi6OFgMuFd2p-SjVldDD43KzI4oeQKxVtAyGLhVjtKK74W7YvTFwenpQ3N1O7qsm_pmhNSzZYaQMtK0yWDuKAW41aPsWdbTD-rNBLeEMXqXecMYDmuE15hhi2BNYkY4wAzNkLPP5ClGwRJT8J6A5pDWNb9zJesXwcoWqOfv9F992RSceMyL4-FN29qRR8qzOs-UBWGNGuCX7avOa01Gvw"
    try:
        response = get("https://api.vk.ru/method/messages.getHistory?", params={"v": 5.199,"access_token": access_token, "offset": offset, "count": count, "user_id": user_id,})
        return response
    except requests.exceptions.RequestException as e:
        return e


#user_id = get("https://api.vk.com/method/utils.resolveScreenName?screen_name=toxeles&access_token=YOUR_ACCESS_TOKEN&v=5.131")
user_id = 305899701
history = messages_get_history(user_id)

messages = history['response']['items']
dates = count_dates_from_messages(messages)

x_data = list(dates.keys())
y_data = []

for key in x_data:
    y_data.append(dates[key])
    
fig = go.Figure()
fig.add_trace(go.Scatter(x=x_data, y=y_data, mode='lines+markers', name='Количетсво'))
fig.update_layout(title='График сообщений', xaxis_title='Дата', yaxis_title='Количество')
fig.show()