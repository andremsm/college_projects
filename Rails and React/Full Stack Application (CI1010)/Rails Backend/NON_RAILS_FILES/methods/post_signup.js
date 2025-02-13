import fetch from "node-fetch";

fetch("http://localhost:3010/signup", {
	headers: {
		accept: "text/html, application/xhtml+xml, application/json",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	body: JSON.stringify({ login: "guest", password: "guest" }),
	method: "POST",
})
	.then((response) => response.json())
	.then((data) => {
		// Handle the response data
		console.log(data);
	})
	.catch((error) => {
		// Handle any errors
		console.error("Error:", error);
	});
