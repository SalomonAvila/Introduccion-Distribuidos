#!/bin/bash

set -e

echo " Pods "
kubectl get pods -n biblioteca

echo ""
echo " Logs load-manager "
kubectl logs -n biblioteca deploy/load-manager --tail=50 || true

echo ""
echo "Logs requester-ps "
kubectl logs -n biblioteca job/requester-ps --tail=100 || true

echo ""
echo " Logs actor-prestamo "
kubectl logs -n biblioteca deploy/actor-prestamo --tail=50 || true

echo ""
echo " Logs actor-devolucion "
kubectl logs -n biblioteca deploy/actor-devolucion --tail=50 || true

echo ""
echo " Logs actor-renovacion "
kubectl logs -n biblioteca deploy/actor-renovacion --tail=50 || true
