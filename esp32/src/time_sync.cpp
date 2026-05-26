#include "time_sync.h"
#include <time.h>
#include <sys/time.h>
#include "wifi_manager.h"

static bool timeSynchronized = false;

bool synchronizeTime()
{
  if (!isWiFiConnected())
  {
    Serial.println("Brak polaczenia sieciowego podczas synchronizacji");
    timeSynchronized = false;
    return false;
  }

  configTime(0, 0, "pool.ntp.org", "time.nist.gov", "time.google.com");

  Serial.println("Synchronizacja czasu...");

  struct tm timeinfo;
  int attempts = 0;
  const int maxAttempts = 20;

  while (!getLocalTime(&timeinfo) && attempts < maxAttempts)
  {
    Serial.println("Oczekiwanie na synchronizacje czasu...");
    delay(500);
    attempts++;
  }

  if (attempts >= maxAttempts)
  {
    Serial.println("Nie udalo sie zsynchronizowac czasu. Uzywam millis() jako fallback.");
    timeSynchronized = false;
    return false;
  }

  Serial.println("Czas zsynchronizowany.");
  timeSynchronized = true;
  return true;
}

long long getTimestampMs()
{
  if (!timeSynchronized)
  {
    return (long long)millis();
  }

  struct timeval tv;
  gettimeofday(&tv, NULL);

  return ((long long)tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);
}

bool isTimeSynchronized()
{
  return timeSynchronized;
}