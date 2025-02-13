import axios from "axios";

const API_URL = "http://10.56.14.26:8080/api/auth/";

export function login(username: string, password: string) {
	return axios
		.post(API_URL + "signin", {
			username,
			password,
		})
		.then((response) => {
			if (response.data.accessToken) {
				localStorage.setItem("user", JSON.stringify(response.data));
				console.log(JSON.stringify(response.data));
			}

			return response.data;
		});
}

export function logout() {
	localStorage.removeItem("user");
	localStorage.removeItem("admin");
	localStorage.removeItem("username");
	window.location.reload();
}

export function getCurrentUser() {
	const userStr = localStorage.getItem("user");
	if (userStr) return userStr;

	return undefined;
}

export function getAuthStatus() {
	const userStr = localStorage.getItem("admin");
	if (userStr) return userStr;

	return undefined;
}

export function getUsername() {
	const userStr = localStorage.getItem("username");
	if (userStr) return userStr;

	return undefined;
}

export function authExpiration() {
	const parseJwt = (token: string) => {
		try {
			return JSON.parse(window.atob(token.split(".")[1]));
		} catch (e) {
			console.log("error?");
			return null;
		}
	};
	const user = getCurrentUser();
	//console.log(user);
	if (user) {
		const decodedJwt = parseJwt(user);
		//console.log(decodedJwt.exp * 1000 - Date.now());
		if (decodedJwt.exp * 1000 < Date.now()) {
			localStorage.removeItem("user");
			return undefined;
		} else return user;
	} else return undefined;
}
