#!/bin/bash

docker build -t biblioteca/load-manager:latest -f docker/Dockerfile.gc .
docker build -t biblioteca/requester-ps:latest -f docker/Dockerfile.ps .
docker build -t biblioteca/actor-prestamo:latest -f docker/Dockerfile.actor-prestamo .
docker build -t biblioteca/actor-devolucion:latest -f docker/Dockerfile.actor-devolucion .
docker build -t biblioteca/actor-renovacion:latest -f docker/Dockerfile.actor-renovacion .
kubectl apply -f k8s/00-namespace.yaml
kubectl apply -f k8s/00-configmap-requests.yaml
kubectl apply -f k8s/20-actor-prestamo.yaml
kubectl apply -f k8s/10-load-manager.yaml
kubectl apply -f k8s/30-actor-devolucion.yaml
kubectl apply -f k8s/40-actor-renovacion.yaml
kubectl get pods -n biblioteca
