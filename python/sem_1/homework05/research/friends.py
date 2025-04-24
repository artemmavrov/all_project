import dataclasses
import requests
from func_get import get
import math
import time
import typing as tp

#from vkapi import config, session
#from vkapi.exceptions import APIError

QueryParams = tp.Optional[tp.Dict[str, tp.Union[str, int]]]


@dataclasses.dataclass(frozen=True)
class FriendsResponse:
    count: int
    items: tp.Union[tp.List[int], tp.List[tp.Dict[str, tp.Any]]]


def get_friends(
    user_id: int, count: int = 5000, offset: int = 0, fields: tp.Optional[tp.List[str]] = None
):
    """
    Получить список идентификаторов друзей пользователя или расширенную информацию
    о друзьях пользователя (при использовании параметра fields).

    :param user_id: Идентификатор пользователя, список друзей для которого нужно получить.
    :param count: Количество друзей, которое нужно вернуть.
    :param offset: Смещение, необходимое для выборки определенного подмножества друзей.
    :param fields: Список полей, которые нужно получить для каждого пользователя.
    :return: Список идентификаторов друзей пользователя или список пользователей.
    """
    assert isinstance(user_id, int), "user_id must be positive integer"
    assert isinstance(fields, tp.Optional[tp.List]), "fields must be list"
    assert user_id > 0, "user_id must be positive integer"
    # PUT YOUR CODE HERE
    access_token = "vk1.a.huvJzw4XO-zr0bkhv11hBWzmUTZTSKOrcmin3gQzyZ18vd2j9QFchJqAggOk9whL0FWaFHNxeTP5UkNRbWNd_KoS2IQdk4rz5OSE4RJfRCSYHl0-kzJCW-0G4b9hnmU9s5iPD9oPnGV0jywafaF-R_RiK0k13kJ5IbLA9gEjde0Td7cSo7PcTSPzh3OETCyj"
    #305899701
    #user_id = 806524892
    try:
        response = get("https://api.vk.ru/method/friends.get?",
                       params={"v": 5.199, "access_token": access_token, "offset": offset, "count": count,
                               "user_id": user_id,  "fields": fields})
        items = response["response"]["items"]
        date = []
        for item in items:
            if "bdate" in item.keys() and item["bdate"].count(".") == 2:
                date.append(item["bdate"])
        return date
    except requests.exceptions.RequestException as e:
        return e




class MutualFriends(tp.TypedDict):
    
    id: int
    common_friends: tp.List[int]
    common_count: int


def get_mutual(
    source_uid: tp.Optional[int] = None,
    target_uid: tp.Optional[int] = None,
    target_uids: tp.Optional[tp.List[int]] = None,
    order: str = "",
    count: tp.Optional[int] = None,
    offset: int = 0,
    progress=None,
) -> tp.Union[tp.List[int], tp.List[MutualFriends]]:
    """
    Получить список идентификаторов общих друзей между парой пользователей.

    :param source_uid: Идентификатор пользователя, чьи друзья пересекаются с друзьями пользователя с идентификатором target_uid.
    :param target_uid: Идентификатор пользователя, с которым необходимо искать общих друзей.
    :param target_uids: Cписок идентификаторов пользователей, с которыми необходимо искать общих друзей.
    :param order: Порядок, в котором нужно вернуть список общих друзей.
    :param count: Количество общих друзей, которое нужно вернуть.
    :param offset: Смещение, необходимое для выборки определенного подмножества общих друзей.
    :param progress: Callback для отображения прогресса.
    """
    pass
