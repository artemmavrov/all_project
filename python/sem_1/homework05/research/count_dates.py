from datetime import datetime

def count_dates_from_messages(messages):
    dates = dict()
    
    for message in messages:
        date = datetime.fromtimestamp(message['date']).strftime("%Y-%m-%d %H:%M:%S")
        if date not in dates.keys():
            dates[date] = 1
        else:
            dates[date] += 1
            
    return dates
