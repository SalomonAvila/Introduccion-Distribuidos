#!/bin/bash
# Script bash para generar datos en Redis
# Alternativa simple sin dependencias de Python

REDIS_HOST=${1:-localhost}
REDIS_PORT=${2:-6379}
COUNTER=0

echo "🚀 Iniciando generador de datos para Redis"
echo "Host: $REDIS_HOST:$REDIS_PORT"
echo "Press Ctrl+C para detener"

while true; do
    COUNTER=$((COUNTER + 1))
    
    # Genera datos aleatorios
    RANDOM_VALUE=$((RANDOM % 1000))
    USER_ID=$((RANDOM % 100))
    EVENT_TYPE=$(echo "login logout purchase view click" | tr ' ' '\n' | shuf -n1)
    TIMESTAMP=$(date -u +%Y-%m-%dT%H:%M:%S)
    
    # Envía comandos a Redis
    {
        echo "SET data:$COUNTER '$TIMESTAMP|$RANDOM_VALUE|user_$USER_ID|$EVENT_TYPE' EX 3600"
        echo "INCR total_operations"
        echo "INCR operations_by_type:$EVENT_TYPE"
        echo "LPUSH event_queue '$COUNTER:$EVENT_TYPE'"
        echo "HSET user:$USER_ID last_event $EVENT_TYPE timestamp '$TIMESTAMP'"
        echo "SADD active_users user_$USER_ID"
        echo "SADD events_today $EVENT_TYPE"
        echo "GET data:$((COUNTER - RANDOM % 100))"
    } | redis-cli -h $REDIS_HOST -p $REDIS_PORT > /dev/null
    
    # Muestra progreso cada 10 operaciones
    if [ $((COUNTER % 10)) -eq 0 ]; then
        KEYS=$(redis-cli -h $REDIS_HOST -p $REDIS_PORT DBSIZE | grep keys | awk '{print $2}')
        echo "[$(date +%H:%M:%S)] Ops: $COUNTER | Keys: $KEYS"
    fi
    
    # Pequeña pausa
    sleep 0.1
done
