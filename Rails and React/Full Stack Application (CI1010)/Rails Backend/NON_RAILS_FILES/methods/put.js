import fetch from "node-fetch";

const studentId = 30; // ID of the student to be updated

fetch(`http://localhost:3010/students/${studentId}`, {
	headers: {
		"Content-type": "application/json",
	},
	body: JSON.stringify({
		token: "eyJhbGciOiJIUzI1NiJ9.eyJ1c2VyX2RhdGEiOjF9.wATB1jNqZ0dvJBekmoL8mh29MysD9RxOtmu9sr66vV4",
		student: { name: "asdfasdf", course_id: 2, enrolment: "GRR00000051" },
	}), // Updated data
	method: "PUT",
});
