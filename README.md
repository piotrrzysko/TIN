AdvertCast
========

### Wymagania

* CMake 3.0.2
* Docker 1.9.1

### Uruchamianie

1.  Z katalogu /scripts uruchomić skrypt run-containers.sh jako argumenty podając adresy ip kontenerów.
    _Przykład: ./run-containers.sh 10.1.1.2 10.1.1.3_

2.  Z katalogu /scripts uruchomić deploy.sh. Argumenty: `[katalog do wgrania] [lista adresów ip]`
    _Przykład: ./deploy.sh ../build 10.1.1.2 10.1.1.3_
