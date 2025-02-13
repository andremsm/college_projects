import fetch from "node-fetch";

fetch("http://localhost:3000/students", {
	headers: {
		accept: "text/html, application/xhtml+xml, application/json",
		Referer: "http://localhost:3000/students",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
	method: "POST",
});
