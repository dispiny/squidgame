package main

import (
	"log"
	"net/http"
)

// func mainHandler(w http.ResponseWriter, r *http.Request) {
// 	fmt.Fprintf(w, "Hi there, I love %s!", r.URL.Path[1:])
// }

func main() {
	// http.HandleFunc("/", mainHandler)

	http.Handle("/", http.FileServer(http.Dir("public")))
	log.Fatal(http.ListenAndServe(":8080", nil))
}
