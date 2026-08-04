#!/bin/bash

kubectl delete job requester-ps -n biblioteca
kubectl apply -f k8s/50-ps-job.yaml
