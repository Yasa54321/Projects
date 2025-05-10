package main

import (
	"context"
	"fmt"
	"log"

	"github.com/chromedp/cdproto/cdp"
	"github.com/chromedp/chromedp"
)

type Product_to_scrape struct {
	name  string
	price string
}

func main() {

	//slice to hold products_class objects
	var products_slice []Product_to_scrape
	var name, price string

	fmt.Println("Hello World")

	ctx, cancel := chromedp.NewContext( //
		context.Background(), //creates teh root context broser window which doesnt ahve anything
	)
	defer cancel() //this releases all of the resources when the function is done

	scrollingScript := `
		const scrolls = 8
		let scrollCount = 0

		const scrollInterval = setInterval(() => {
			window.scrollTo(0,document.body.scrollHeight)
			scrollCount++

			if (scrollCount == scrolls){
				clearInterval(scrollInterval)
			}



		}, 500)
	`
	var dom_element_nodes []*cdp.Node
	err := chromedp.Run(ctx, chromedp.Navigate("https://scrapingclub.com/exercise/list_infinite_scroll/"), chromedp.Evaluate(scrollingScript, nil), chromedp.WaitVisible(".post:nth-child(60)"), chromedp.Nodes(".post", &dom_element_nodes, chromedp.ByQueryAll))

	if err != nil {
		log.Fatal("Error is ", err)

	}

	for _, node := range dom_element_nodes {
		err = chromedp.Run(ctx, chromedp.Text("h4", &name, chromedp.ByQuery, chromedp.FromNode(node)), chromedp.Text("h5", &price, chromedp.ByQuery, chromedp.FromNode(node)))
		if err != nil {

			log.Fatal("The error is ", err)
		}

		product := Product_to_scrape{}
		product.name = name
		product.price = price

		products_slice = append(products_slice, product)

	}

	fmt.Println(products_slice)

}
