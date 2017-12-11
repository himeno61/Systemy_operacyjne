# Synchronizacja procesów z wykorzystaniem semaforów i wątków z wykorzystaniem monitorów

Rozważmy następujący problem obsługi przychodzących zamówień. Mamy danych n producentów
dostarczających towar jednemu odbiorcy. Odbiorca odsprzedaje otrzymane towary z zyskiem, ale czas
w którym może tego dokonać jest zależny od sytuacji na rynku i nie jest znany. Na szczęście
dysponuje magazynem, w którym może w jednym czasie przechowywać m towarów. Proszę
zorganizować obsługę magazynu w taki sposób, aby odbiorca mógł prowadzić sprzedaż jeżeli tylko,
któryś z producentów wytworzył już swój produkt i jednocześnie nie dopuścić do przepełnienia
magazynu lub zniszczenia znajdującego się tam towaru. Każdy producent powinien przekazać k
jednostek towaru.

# Demonstracja działania algorytmu synchronizacji:
uruchamiamy program **./handel n m k**
gdzie:
**n** – liczba procesów producentów
**m** – rozmiar kolejki
**k** – liczba jednostek towaru, czyli liczb, które powinien wstawić każdy producent do bufora
W ramach programu należy zadbać o utworzenie procesów potomnych realizujących określone
funkcje. Każdy producent i odbiorca powinien wypisywać na konsoli wykonywane operacje w celu
demonstracji działania programu.

