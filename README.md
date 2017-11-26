# Moduł do obsługi tablic LED

Moduł ma umożliwić komunikację zewnętrznych systemów z tablicami LED wykorzystywanymi w systemach parkingowych i logistycznych  firmy LOGBIT. Głównym celem jest integracja systemów LOGBIT z oprogramowaniem do rozpoznawania tablic rejestracyjnych.

## UWAGA

Oprogramowanie dedykowane dla urządzeń firmy LOGBIT.

### Wymagania Sprzętowe

- Minikomputer oparty o procesory z rodziny ARM Cortex z systemem opartym o Linux'a np. raspberry PI z raspabianem lub Orange PI z DietPi, minimum jeden port USB, połączenie sieciowe WIFI lub Ethernet (zalecane stałe IP). 
- przejściówka USB na RS485 (sterownik CH340)
- tablica LED ze sterownikiem firmy LOGBIT

### Wymagania Software

- linux lub embeded system oparty o linux'a, kernel minimum 4.x
- gcc/g++ minimum 7.x (polecana wersja 7.2.0) (wymagana flaga ```-std=c++11```) 
- [nlohmann-json](https://github.com/nlohmann/json/releases) biblioteka do obsługi formatu json


What things you need to install the software and how to install them

```
Give examples
```

### Instalacja


A step by step series of examples that tell you have to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Test

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

## Wersja

- 1.0


## Authors

* **Dominik Kesselring""
