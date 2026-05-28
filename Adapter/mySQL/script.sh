#!/bin/bash 
docker build -t mi-adapter-local .
minikube image load mi-adapter-local
kubectl delete pod adapter-health
kubectl apply -f pod-adapter.yaml
kubectl get pods