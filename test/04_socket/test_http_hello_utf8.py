import requests


def test_hello():
    res = requests.get("http://127.0.0.1:8000")

    assert res.status_code == 200
    assert res.reason == "OK"
    assert res.encoding == "UTF-8"
    assert res.headers["Content-Type"] == "text/html; charset=UTF-8"
    assert res.headers["Content-Length"] == "15"
    assert res.text == "こんにちは"
