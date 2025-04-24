import datetime as dt
import statistics
import typing as tp
from friends import get_friends


def age_predict(user_id: int) -> tp.Optional[float]:
    friends = get_friends(user_id, fields=["bdate"])
    date = dt.datetime(dt.date.today().year, dt.date.today().month, dt.date.today().day)
    count = len(friends)
    sm = 0
    
    for friend in friends:
        friend = dt.datetime.strptime(friend, "%d.%m.%Y")
        difference = date - friend
        sm += difference.days
        
    return sm / (count * 365)


print(age_predict(538975083))