import "bulma/css/bulma.css";
import "bulma/css/bulma.min.css";
import "./App.css";
import { useState, useEffect } from "react";
import {
	authExpiration,
	getAuthStatus,
	getCurrentUser,
	getUsername,
} from "./Utils";
import "./glyphs/style.css";
import {
	AdminInfo,
	CoursesModal,
	EditCourse,
	EditMajor,
	EditStudent,
	LoginModal,
	LogoutButton,
	MainInfo,
	MajorsModal,
	NewCourse,
	NewMajor,
	NewStudent,
	RemoveCourse,
	RemoveMajor,
	RemoveStudent,
} from "./components";

function LandingPage(props: any) {
	return (
		<div>
			<p>{props.majors[0].courses}</p>
			<p>{props.majors[0].name}</p>
		</div>
	);
}

function App() {
	const [loading, setLoading] = useState(true);
	const [loggedIn, setLoggedIn] = useState(false);
	const [isAdmin, setIsAdmin] = useState(false);

	const [majorsJson, setMajorsJson] = useState([]);
	const [courseNames, setCourseNames] = useState([]);
	const [courseCheckbox, setCourseCB] = useState([]);
	const [majorNames, setMajorNames] = useState([]);
	const [studentNames, setStudentNames] = useState([]);
	const [majorList, setMajorList] = useState([]);
	const [courseNamesPlain, setCourseNamesPlain] = useState([]);
	const [majorNamesPlain, setMajorNamesPlain] = useState([]);

	const [fetchMajors, setFetchMajors] = useState([]);
	const [fetchCourses, setFetchCourses] = useState([]);
	const [fetchStudents, setFetchStudents] = useState([]);
	const [fetchEnrolments, setFetchEnrolments] = useState([]);

	const [majorsIsFetched, setMajorsFetched] = useState(false);
	const [coursesIsFetched, setCoursesFetched] = useState(false);
	const [studentsIsFetched, setStudentsFetched] = useState(false);
	const [enrolmentsIsFetched, setEnrolmentsFetched] = useState(false);

	// fetch all data
	useEffect(() => {
		const auth = getCurrentUser();
		const admin = getAuthStatus();
		if (auth) {
			setLoggedIn(true);
			//setLoading(false);
			if (admin === "true") setIsAdmin(true);
		}
		fetch("http://localhost:3010/majors.json", {
			headers: {
				"Content-type": "application/json; charset=UTF-8",
				//"x-access-token": access_token,
				"Access-Control-Allow-Origin": "http://localhost:3001",
			},
			cache: "no-store",
			method: "GET",
		})
			.then((response) => {
				return response.json();
			})
			.then((jsonFile) => {
				setFetchMajors(jsonFile);
				setMajorsFetched(true);
			});
		fetch("http://localhost:3010/courses.json", {
			headers: {
				"Content-type": "application/json; charset=UTF-8",
				//"x-access-token": access_token,
				"Access-Control-Allow-Origin": "http://localhost:3001",
			},
			cache: "no-store",
			method: "GET",
		})
			.then((response) => {
				return response.json();
			})
			.then((jsonFile) => {
				setFetchCourses(jsonFile);
				setCoursesFetched(true);
			});
		fetch("http://localhost:3010/students.json", {
			headers: {
				"Content-type": "application/json; charset=UTF-8",
				//"x-access-token": access_token,
				"Access-Control-Allow-Origin": "http://localhost:3001",
			},
			cache: "no-store",
			method: "GET",
		})
			.then((response) => {
				return response.json();
			})
			.then((jsonFile) => {
				setFetchStudents(jsonFile);
				setStudentsFetched(true);
			});
		fetch("http://localhost:3010/enrolments.json", {
			headers: {
				"Content-type": "application/json; charset=UTF-8",
				//"x-access-token": access_token,
				"Access-Control-Allow-Origin": "http://localhost:3001",
			},
			cache: "no-store",
			method: "GET",
		})
			.then((response) => {
				return response.json();
			})
			.then((jsonFile) => {
				setFetchEnrolments(jsonFile);
				setEnrolmentsFetched(true);
			});
	}, []);

	// all data has been fetched
	useEffect(() => {
		if (
			majorsIsFetched &&
			coursesIsFetched &&
			studentsIsFetched &&
			enrolmentsIsFetched
		) {
			const majorsArray: any = [];
			const courseNamesArray: any = [];
			const majorNamesArray: any = [];
			const studentNamesArray: any = [];
			//console.log(jsonFile);
			fetchMajors.forEach((item: any, index: number) => {
				majorNamesArray.push(item.name);
				const coursesDiv: any = [];
				//majors.name = item.name;
				//majors.courses = item.courses;
				//console.log(item.courses);
				item.courses.forEach((itemCourse: any, index: number) => {
					//console.log("==================");
					//console.log("itemCourse.courses");
					//console.log("==================");
					//console.log(itemCourse.name);
					if (!courseNamesArray.includes(itemCourse.name))
						courseNamesArray.push(itemCourse.name);
					const students = fetchStudents.filter(
						(obj: any, index, array) => {
							//console.log(
							//	obj.course_id.toString() + " =? " + itemCourse.id.toString()
							//);
							return obj.course_id === itemCourse.id;
						}
					);
					//console.log("STUDENTS:");
					//console.log(students);
					const studentsElem: any = [];
					students.forEach((itemStudent: any, index: number) => {
						/*
						console.log("======================");
						console.log(itemStudent);
						console.log(item);
						console.log("======================");
						*/
						if (
							!studentNamesArray.find(
								(itemArray: any) =>
									itemArray.enrolment ===
									itemStudent.enrolment.code
							)
						)
							studentNamesArray.push({
								name: itemStudent.name,
								enrolment: itemStudent.enrolment.code,
								course: itemStudent.course_name.name,
							});
						const enrolment = itemStudent.enrolment
							? itemStudent.enrolment.code
							: "Não consta";
						studentsElem.push(
							<div
								key={"studentElem" + index}
								style={{ clear: "both" }}
							>
								<p>
									<span
										style={{ float: "left" }}
										className="mx-6 is-float-left"
									>
										{itemStudent.name}
									</span>
									<span
										style={{ float: "right" }}
										className="mx-6 is-float-right"
									>
										{enrolment}
									</span>
								</p>
							</div>
						);
					});
					//console.log("===========");
					const course = Object.freeze({
						name: itemCourse.name,
						codename: itemCourse.codename,
						students: studentsElem,
						enrolments: "b",
					});
					coursesDiv.push(
						<CoursesModal
							key={index.toString() + "cool"}
							courses={course}
						></CoursesModal>
					);
				});
				let majors: any = Object.freeze({
					name: item.name,
					courses: coursesDiv,
				});
				majorsArray.push(
					<MajorsModal key={index} majors={majors}></MajorsModal>
				);
				//console.log(majors.courses);
				//console.log(item.name);
			});
			const courseObj: any = [];
			const courseCheckbox: any = [];
			setCourseNamesPlain(courseNamesArray);
			setMajorNamesPlain(majorNamesArray);
			courseNamesArray.forEach((item: any, index: number) => {
				courseObj.push(
					<option key={"courseObj" + index.toString()}>{item}</option>
				);
				courseCheckbox.push(
					<label
						key={"courseCheckbox" + index.toString()}
						className="checkbox"
					>
						<div>
							<input type="checkbox"></input>
							&nbsp;{item}&nbsp;&nbsp;&nbsp;
						</div>
					</label>
				);
			});
			const majorObj: any = [];
			const majorList: any = [];
			majorNamesArray.forEach((item: any, index: number) => {
				majorList.push(
					<option key={"majorList" + index.toString()}>{item}</option>
				);
				majorObj.push(
					<label
						key={"majorObj" + index.toString()}
						className="checkbox"
					>
						<div>
							<input
								className={"majorCheckbox" + index.toString()}
								type="checkbox"
							></input>
							&nbsp;{item}&nbsp;&nbsp;&nbsp;
						</div>
					</label>
				);
			});
			const studentObj: any = [];
			studentNamesArray.forEach((item: any, index: number) => {
				studentObj.push(
					<option key={"studentObj" + index.toString()}>
						{item.name + " - " + item.course}
					</option>
				);
			});
			//console.log("console.log(studentNamesArray);");
			//console.log("===============================");
			//console.log(studentObj);
			//console.log("===============================");
			setCourseNames(courseObj);
			setCourseCB(courseCheckbox);
			setMajorNames(majorObj);
			setStudentNames(studentObj);
			setMajorList(majorList);
			setMajorsJson(majorsArray);
			//console.log(majorsArray);
			setLoading(false);
		}
	}, [
		fetchMajors,
		fetchStudents,
		majorsIsFetched,
		coursesIsFetched,
		studentsIsFetched,
		enrolmentsIsFetched,
	]);

	const pageLayout = isAdmin ? (
		<div className="is-widescreen">
			<div className="columns">
				<aside className="menu is-left-aligned">
					<div style={{ display: "flex" }}>
						<strong className="menu-label">Admin</strong>
						<AdminInfo></AdminInfo>
					</div>
					<p className="menu-label">Criar</p>
					<ul className="menu-list">
						<li key={"NewStudent"}>
							<NewStudent
								courseNames={courseNames}
								json={fetchCourses}
							></NewStudent>
						</li>
						<li key={"NewCourse"}>
							<NewCourse
								majorNames={majorNames}
								majorNamesPlain={majorNamesPlain}
								json={fetchMajors}
							></NewCourse>
						</li>
						<li key={"NewMajor"}>
							<NewMajor
								courseNames={courseCheckbox}
								courseNamesPlain={courseNamesPlain}
								json={fetchCourses}
							></NewMajor>
						</li>
					</ul>
					<p className="menu-label">Editar</p>
					<ul className="menu-list">
						<li key={"EditStudent"}>
							<EditStudent
								studentNames={studentNames}
								courseNames={courseNames}
								json={fetchCourses}
							></EditStudent>
						</li>
						<li key={"EditCourse"}>
							<EditCourse
								courseNames={courseNames}
								majorNames={majorNames}
								majorNamesPlain={majorNamesPlain}
								json={fetchCourses}
								jsonMajors={fetchMajors}
							></EditCourse>
						</li>
						<li key={"EditMajor"}>
							<EditMajor
								majorNames={majorList}
								courseNames={courseCheckbox}
								courseNamesPlain={courseNamesPlain}
								json={fetchMajors}
								jsonCourses={fetchCourses}
								loading={loading}
							></EditMajor>
						</li>
					</ul>
					<p className="menu-label">Remover</p>
					<ul className="menu-list">
						<li key={"RemoveStudent"}>
							<RemoveStudent
								studentNames={studentNames}
								courseNames={courseNames}
								json={fetchCourses}
							></RemoveStudent>
						</li>
						<li key={"RemoveCourse"}>
							<RemoveCourse
								courseNames={courseNames}
								majorNames={majorNames}
								json={fetchCourses}
							></RemoveCourse>
						</li>
						<li key={"RemoveMajor"}>
							<RemoveMajor
								majorNames={majorList}
								courseNames={courseCheckbox}
								json={fetchMajors}
							></RemoveMajor>
						</li>
					</ul>
				</aside>
				<div className="column content">
					<section className="section">
						<h1 className="title is-left-aligned mx-2">
							Bem vindo,{" "}
							{getUsername()
								? getUsername()
								: "usuário não identificado"}
						</h1>
					</section>

					<div style={{ display: "flex", marginLeft: "10vh" }}>
						<p>Clique nos icones</p>&nbsp; <MainInfo></MainInfo>
						&nbsp;
						<p>
							(esse ícone é clicável) para entender o
							funcionamento da página
						</p>
					</div>
					{loggedIn ? (
						loading ? (
							<div>&nbsp;</div>
						) : (
							<LogoutButton></LogoutButton>
						)
					) : loading ? (
						<div></div>
					) : (
						<LoginModal></LoginModal>
					)}
					<header className="App-header">
						<div className="columns is-multiline">
							{
								//<LandingPage majors={majorsJson}></LandingPage>
								majorsJson
								//<MajorsModal majors={majorsJson}></MajorsModal>
							}
						</div>
					</header>
				</div>
			</div>
		</div>
	) : (
		<div>
			<section className="section">
				<h1
					className="title is-left-aligned mx-2"
					style={{ marginBottom: "-4vh" }}
				>
					Bem vindo,{" "}
					{getUsername() ? getUsername() : "usuário não identificado"}
				</h1>
			</section>
			<div style={{ display: "flex", marginLeft: "10vh" }}>
				<p>Clique nos icones</p>&nbsp; <MainInfo></MainInfo>&nbsp;
				<p>
					(esse ícone é clicável) para entender o funcionamento da
					página
				</p>
			</div>
			{loggedIn ? (
				loading ? (
					<div>&nbsp;</div>
				) : (
					<LogoutButton></LogoutButton>
				)
			) : loading ? (
				<div></div>
			) : (
				<LoginModal></LoginModal>
			)}
			<header className="App-header">
				<div className="columns is-multiline">
					{
						//<LandingPage majors={majorsJson}></LandingPage>
						majorsJson
						//<MajorsModal majors={majorsJson}></MajorsModal>
					}
				</div>
			</header>
		</div>
	);

	return (
		<div className="App">
			<section className="hero is-primary">
				<div className="hero-body">
					<p className="title">
						Visualizador de Cursos/Disciplinas/Matrículas
					</p>
					<p className="subtitle">
						Trabalho 5 de CI1010 - Programação Web
					</p>
				</div>
			</section>
			{pageLayout}
		</div>
	);
}

export default App;
