package main

import (
	"database/sql"
	"flag"
	"fmt"
	"net/http"

	_ "github.com/go-sql-driver/mysql"
)

var (
	user   = flag.String("user", "root", "The database user name")
	passwd = flag.String("password", "password", "The database password")
	dbName = flag.String("database", "mysql", "The database to connect to")
	query  = flag.String("query", "SELECT 1", "The test query")
	addr   = flag.String("address", ":8080", "The address to listen on")
)

func main() {
	flag.Parse()
	
	dsn := fmt.Sprintf("%s:%s@tcp(localhost:3306)/%s", *user, *passwd, *dbName)
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		fmt.Printf("Error opening database: %v\n", err)
	}

	http.HandleFunc("/healthz", func(res http.ResponseWriter, req *http.Request) {
		_, err := db.Exec(*query)
		if err != nil {
			res.WriteHeader(http.StatusInternalServerError)
			res.Write([]byte(err.Error()))
			return
		}
		res.WriteHeader(http.StatusOK)
		res.Write([]byte("OK"))
	})

	fmt.Printf("Starting adapter on %s...\n", *addr)
	http.ListenAndServe(*addr, nil)
}