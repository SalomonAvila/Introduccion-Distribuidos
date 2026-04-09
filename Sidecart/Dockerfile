FROM gcc:latest AS builder  
COPY main.cpp .  
RUN g++ -o mi_app_cpp main.cpp  
 
FROM fedora:latest  
COPY --from=builder /mi_app_cpp /mi_app_cpp  
CMD ["./mi_app_cpp"]