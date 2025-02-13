import fetch from "node-fetch";

fetch("http://localhost:3000/students/3", {
	headers: {
		accept: "text/html, application/xhtml+xml, application/json",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
	method: "DELETE",
});
