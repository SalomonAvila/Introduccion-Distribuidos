FROM golang:1.24-alpine
WORKDIR /app
RUN go mod init adapter && go get github.com/go-sql-driver/mysql
COPY main.go .
RUN go build -o adapter main.go
CMD ["./adapter"]