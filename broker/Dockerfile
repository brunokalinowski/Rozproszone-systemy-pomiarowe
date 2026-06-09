# Krok 1: Wybierz obraz bazowy.
FROM eclipse-mosquitto:latest

# Krok 2: Skopiuj nasz plik konfiguracyjny.
COPY mosquitto.conf /mosquitto/config/mosquitto.conf

# Twórcy obrazu eclipse-mosquitto 
# już zdefiniowali w swoim Dockerfile komende startowa: 
# CMD ["/usr/sbin/mosquitto", "-c", "/mosquitto/config/mosquitto.conf"] 
# (To jest komenda, która fizycznie uruchamia serwer brokera).

COPY certs /mosquitto/certs

RUN chmod 644 /mosquitto/certs/*

EXPOSE 8883
