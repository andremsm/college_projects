import fetch from "node-fetch";

fetch("http://localhost:3010/courses", {
	headers: {
		accept: "text/html, application/xhtml+xml, application/json",
		Referer: "http://localhost:3000/courses",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	body: JSON.stringify({
		course: {
			name: "Engenharia de Software",
			codename: "CI1221",
			major_ids: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
			token: "eyJhbGciOiJIUzI1NiJ9.eyJ1c2VyX2RhdGEiOjJ9.nEKSlNUFknc-LwzYtSUGhSnaJYqfwRmdbsOM2HTjxvk",
		},
	}),
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
