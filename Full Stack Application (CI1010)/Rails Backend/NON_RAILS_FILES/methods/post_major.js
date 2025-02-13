import fetch from "node-fetch";

fetch("http://localhost:3000/majors", {
	headers: {
		accept: "text/html, application/xhtml+xml, application/json",
		Referer: "http://localhost:3000/majors",
		"Referrer-Policy": "strict-origin-when-cross-origin",
		"Content-type": "application/json",
	},
	body: JSON.stringify({
		major: {
			name: "Informática Biomédica",
			course_ids: [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],
		},
	}),
	method: "POST",
});
