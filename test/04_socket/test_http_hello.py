import requests


def test_hello():
    res = requests.get("http://127.0.0.1:8080")

    assert res.status_code == 200
    assert res.reason == "OK"
    assert res.encoding == "ISO-8859-1"
    assert res.headers["Content-Type"] == "text/html"
    assert res.headers["Content-Length"] == "5"
    assert res.text == "HELLO"
