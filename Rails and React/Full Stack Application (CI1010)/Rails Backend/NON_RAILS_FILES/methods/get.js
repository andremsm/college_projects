import fetch from "node-fetch";

fetch("http://localhost:3000/majors", {
	headers: {
		accept: "application/json",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
	method: "GET",
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
