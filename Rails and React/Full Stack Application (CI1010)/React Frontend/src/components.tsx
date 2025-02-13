import { useState, useEffect, useRef } from "react";
import { FontAwesomeIcon } from "@fortawesome/react-fontawesome";
import { icon } from "@fortawesome/fontawesome-svg-core/import.macro";
import { getCurrentUser, logout } from "./Utils";

export function MajorsModal(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal column is-one-quarter">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							{props.majors.name}
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body">
						Disciplinas ofertadas por esse curso:
						<div>&nbsp;</div>
						<div className="columns is-multiline">
							{props.majors.courses}
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<div className="">
				<div className="is-centered">
					<div className="">
						<div
							onClick={handleModalOpen}
							className={"box bhover clickable"}
							style={{
								backgroundColor: "cornflowerblue",
							}}
						>
							<div className="rrow">
								<div className="ccolumn has-text-centered">
									<p>
										<strong style={{ color: "white" }}>
											{props.majors.name}
										</strong>
									</p>
								</div>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
}

export function CoursesModal(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div
			className="Modal column is-half"
			style={{ fontSize: "calc(3px + 2vmin)" }}
		>
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							{props.courses.name}
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>

					<section className="modal-card-body">
						<p
							className="modal-card-subtitle"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							{props.courses.codename}
						</p>
						Alunos matriculados nessa disciplina:
						<div>&nbsp;</div>
						<strong style={{ float: "left" }} className="mx-6">
							Nome
						</strong>
						<strong style={{ float: "right" }} className="mx-6">
							GRR
						</strong>
						<div>&nbsp;</div>
						{props.courses.students}
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<div className="">
				<div className="is-centered">
					<div className="">
						<div
							onClick={handleModalOpen}
							className={"box bhover clickable"}
							style={{
								backgroundColor: "cornflowerblue",
							}}
						>
							<div className="rrow">
								<div className="ccolumn has-text-centered">
									<p>
										<strong style={{ color: "white" }}>
											{props.courses.name}
										</strong>
									</p>
								</div>
							</div>
						</div>
					</div>
				</div>
			</div>
		</div>
	);
}

export function LoginModal(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);

	const [isLoading, setLoading] = useState("");
	const [isDangerLogin, setDangerLogin] = useState("");
	const [isDangerPw, setDangerPw] = useState("");
	const [login, setLogin] = useState("");
	const [password, setPassword] = useState("");
	const [isWrongLoginOrPw, setIsWrongLoP] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	const handleEnter = (event: any) => {
		if (event.key === "Enter") {
			const currentElement = document.activeElement;
			const loginElement = document.getElementById("login");
			const passwordElement = document.getElementById("password");
			if (
				currentElement === loginElement ||
				currentElement === passwordElement
			)
				handleLogin();
		}
	};

	const handleLogin = () => {
		setLoading(" is-loading");
		//console.log(login);
		//console.log(password);
		fetch("http://localhost:3010/login", {
			method: "POST",
			body: JSON.stringify({
				login: login,
				password: password,
			}),
			headers: {
				"Content-type": "application/json; charset=UTF-8",
			},
		})
			.then((response) => {
				if (response.ok) return response.json();
				else throw new Error("Status code error");
			})
			.then((json) => {
				//console.log(json.accessToken);
				localStorage.setItem("user", json.token);
				localStorage.setItem("admin", json.admin);
				localStorage.setItem("username", login);
				//console.log(json.token);
				//console.log(json.admin);
				window.location.reload();
			})
			.catch((err) => {
				//console.log(err)
				setDangerLogin(" is-danger");
				setDangerPw(" is-danger");
				setIsWrongLoP(true);
				setLoading("");
			});
		//console.log(danger);
		//if (danger === "") window.location.reload();
		//setLoading("");
	};

	const wrongLoginPw = isWrongLoginOrPw ? (
		<div>
			<div
				style={{ cursor: "default" }}
				className="has-text-centered has-text-danger is-size-5"
			>
				Usuário ou senha incorreto.
			</div>
		</div>
	) : (
		<div className="hidden is-size-5">&nbsp;</div>
	);

	return (
		<div className="Modal" style={{ fontSize: "calc(3px + 2vmin)" }}>
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title ml-5"
							style={{
								whiteSpace: "pre-line",
								cursor: "default",
							}}
						>
							<i
								style={{
									fontSize: "35px",
									verticalAlign: "middle",
									opacity: "10%",
								}}
								className="icon-portal-in"
							></i>
							<span
								style={{
									marginLeft: "5px",
									marginRight: "5px",
									verticalAlign: "middle",
								}}
							>
								Login
							</span>
							<i
								style={{
									fontSize: "35px",
									verticalAlign: "middle",
									opacity: "10%",
								}}
								className="icon-portal-out"
							></i>
						</p>
						<div
							style={{
								marginLeft: "-5vh",
								float: "none",
								marginRight: "3vh",
							}}
						>
							<LoginInfo></LoginInfo>
						</div>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body">
						<div className="container">
							<div className="columns is-centered">
								<div className="column">
									<div className="box">
										<div className="field">
											{wrongLoginPw}
											<label
												style={{
													zIndex: 1,
													position: "relative",
												}}
												htmlFor=""
												className="label"
											>
												<span
													style={{
														paddingRight: 100,
														paddingLeft: 100,
														paddingBottom: 50,
														backgroundColor:
															"white",
													}}
												>
													Usuário
												</span>
											</label>
											<div
												style={{
													zIndex: 1,
													position: "relative",
												}}
												className="control has-icons-left has-icons-right"
											>
												<input
													id="login"
													type="text"
													placeholder="digite o usuário aqui"
													className={
														"input has-text-centered is-info" +
														isDangerLogin
													}
													required
													value={login}
													onChange={(e) => {
														setIsWrongLoP(false);
														setDangerLogin("");
														setDangerPw("");
														setLogin(
															e.target.value
														);
													}}
													onKeyDown={handleEnter}
												></input>
												<span className="icon is-small is-left">
													<FontAwesomeIcon
														icon={icon({
															name: "user",
															style: "solid",
														})}
													/>
												</span>
												<span className="icon is-small is-right">
													<FontAwesomeIcon
														className="fa-blank"
														icon={icon({
															name: "user",
															style: "solid",
														})}
													/>
												</span>
											</div>
										</div>
										<div className="field">
											<label htmlFor="" className="label">
												Senha
											</label>
											<div className="control has-icons-left has-icons-right">
												<input
													id="password"
													type="password"
													placeholder="*******"
													className={
														"input has-text-centered is-info" +
														isDangerPw
													}
													required
													value={password}
													onChange={(e) => {
														setIsWrongLoP(false);
														setDangerLogin("");
														setDangerPw("");
														setPassword(
															e.target.value
														);
													}}
													onKeyDown={handleEnter}
												></input>
												<span className="icon is-small is-left">
													<FontAwesomeIcon
														icon={icon({
															name: "lock",
															style: "solid",
														})}
													/>
												</span>
												<span className="icon is-small is-right">
													<FontAwesomeIcon
														className="fa-blank"
														icon={icon({
															name: "lock",
															style: "solid",
														})}
													/>
												</span>
											</div>
										</div>

										<div className="field">
											<button
												className={
													"has-icons-right button is-success" +
													isLoading
												}
												onClick={handleLogin}
											>
												Login&nbsp;&nbsp;
												<span className="icon is-small is-right">
													<FontAwesomeIcon
														icon={icon({
															name: "right-to-bracket",
															style: "solid",
														})}
													/>
												</span>
											</button>
										</div>
									</div>
								</div>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>

			<div className="buttons is-right login-button">
				<button className="button is-info" onClick={handleModalOpen}>
					Login&nbsp;&nbsp;&nbsp;
					<span className="icon is-small is-right">
						<FontAwesomeIcon
							icon={icon({
								name: "right-to-bracket",
								style: "solid",
							})}
						/>
					</span>
				</button>
			</div>
		</div>
	);
}

function LoginInfo() {
	const [isModal, setModal] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Informações
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<p className="is-center-aligned">
							Usuários disponíveis:
						</p>
						<br />
						<p>login:admin senha:admin</p>
						<p>
							Usuário com permissões para realizar todas as
							operações.
						</p>
						<br />
						<p>login:guest senha:guest</p>
						<p>
							Usuário sem permissões, não muda a execução se
							comparado a não estar logado.
						</p>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>

			<FontAwesomeIcon
				className="clickable"
				onClick={handleModalOpen}
				enableBackground={"white"}
				icon={icon({
					name: "circle-info",
					style: "solid",
				})}
			/>
		</div>
	);
}

export function MainInfo() {
	const [isModal, setModal] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Informações
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<p>
							Clique em um curso para visualizar as disciplinas
							ofertadas por ele.
						</p>
						<p>
							Clique em uma dessas disciplinas para ver qual aluno
							a está cursando, e qual o seu GRR.
						</p>
						<p>
							Clique no botão login para logar e ver a página como
							um usuário.
						</p>
						<br />
						<p>Relacões:</p>
						<br />
						<p>1x1: Um aluno pode ter apenas uma matrícula</p>
						<p>1xN: Uma disciplina pode ter N Alunos</p>
						<p>
							NxN: Um curso pode ofertar N disciplinas, uma
							disciplinas pode ser ofertada por N cursos
						</p>
						<br />
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>

			<FontAwesomeIcon
				style={{ display: "inline" }}
				className="clickable"
				onClick={handleModalOpen}
				enableBackground={"white"}
				icon={icon({
					name: "circle-info",
					style: "solid",
				})}
			/>
		</div>
	);
}

export function AdminInfo() {
	const [isModal, setModal] = useState(false);

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
		//console.log(props.majors);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Informações
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<p>
							Esse menu aparece apenas quando o usuário é um
							administrador.
						</p>
						<p>
							Aqui é possível criar, editar, e excluir elementos
							do banco de dados.
						</p>

						<br />
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>

			<FontAwesomeIcon
				style={{ display: "inline" }}
				className="clickable"
				onClick={handleModalOpen}
				enableBackground={"white"}
				icon={icon({
					name: "circle-info",
					style: "solid",
				})}
			/>
		</div>
	);
}

export function LogoutButton() {
	const getClass = () => {
		if (getCurrentUser() === "admin") return " logout-button-admin";
		else return " logout-button";
	};

	return (
		<div className={"buttons is-right" + getClass()}>
			<figure className="image logout">
				<img alt="" src="/img/logout.png"></img>
			</figure>
			<button
				className="button is-info has-icons-right"
				style={{
					whiteSpace: "pre-line",
					//paddingRight: 30,
				}}
				onClick={logout}
			>
				Logout&nbsp;&nbsp;&nbsp;
				<span className="icon is-small is-right">
					<FontAwesomeIcon
						icon={icon({
							name: "right-from-bracket",
							style: "solid",
						})}
					/>
				</span>
			</button>
		</div>
	);
}

export function NewStudent(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [name, setName] = useState("");
	const [enrolment, setEnrolment] = useState("");
	const [selected, setSelected] = useState("");
	const [isLoading, setLoading] = useState("");
	const [isHidden, setHidden] = useState(true);

	const post = () => {
		if (!name || !enrolment || !selected) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = "http://localhost:3010/students";
		const course_id = props.json.find((e: any) => e.name === selected).id;

		console.log("posting to: " + url);

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
				student: {
					name: name,
					enrolment: enrolment,
					course_id: course_id,
				},
			}),
			method: "POST",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Novo Aluno
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">GRR</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="GRR00000000"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setEnrolment(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Disciplina</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelected(e.target.value);
										}}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.courseNames}
									</select>
								</div>
							</div>
						</div>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={post}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Novo Aluno</a>
		</div>
	);
}

export function EditStudent(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [isLoading, setLoading] = useState("");
	const [selectedStudent, setSelectedStudent] = useState("");
	const [selectedCourse, setSelectedCourse] = useState("");
	const [isHidden, setHidden] = useState(true);
	const [name, setName] = useState("");
	const [enrolment, setEnrolment] = useState("");

	function student_url() {
		const [student_name, course_name] = selectedStudent.split(" - ");
		const course = props.json.find((e: any) => e.name === course_name);
		const student = course.students.find(
			(e: any) => e.name === student_name
		);
		console.log(student);
		return "http://localhost:3010/students/" + student.id.toString();
	}

	const put = () => {
		/*
		console.log(name);
		console.log(enrolment);
		console.log(selectedStudent);
		console.log(selectedCourse);
		*/

		if (!selectedStudent) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = student_url();
		const course_id = () => {
			if (selectedCourse) {
				if (selectedCourse === "Não Alterar") return "";
				const course = props.json.find(
					(e: any) => e.name === selectedCourse
				);
				return course.id.toString();
			} else return "";
		};

		/*
		console.log("posting to: " + url);
		console.log(token);
		console.log(course_id());
		*/

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
				student: {
					name: name,
					enrolment: enrolment,
					course_id: course_id(),
				},
			}),
			method: "PUT",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Editar Aluno
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Nome</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelectedStudent(e.target.value);
										}}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.studentNames}
									</select>
								</div>
							</div>
						</div>
						<div className="field">
							<label className="label">Novo Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Novo GRR</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="GRR00000000"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setEnrolment(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Disciplina</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelectedCourse(e.target.value);
										}}
									>
										<option>Não Alterar</option>
										{props.courseNames}
									</select>
								</div>
							</div>
						</div>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={put}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Editar Aluno</a>
		</div>
	);
}

export function RemoveStudent(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [isLoading, setLoading] = useState("");
	const [selected, setSelected] = useState("");
	const [isHidden, setHidden] = useState(true);

	function student_url() {
		const [student_name, course_name] = selected.split(" - ");
		const course = props.json.find((e: any) => e.name === course_name);
		const student = course.students.find(
			(e: any) => e.name === student_name
		);
		return "http://localhost:3010/students/" + student.id.toString();
	}

	const postDelete = () => {
		if (!selected) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = student_url();
		console.log("deleting from: " + url);

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
			}),
			method: "DELETE",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Remover Aluno
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Nome</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelected(e.target.value);
										}}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.studentNames}
									</select>
								</div>
							</div>
						</div>

						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={postDelete}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Remover Aluno</a>
		</div>
	);
}

export function NewCourse(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [name, setName] = useState("");
	const [codename, setCodename] = useState("");
	const [selected, setSelected] = useState("");
	const [isLoading, setLoading] = useState("");
	const [isHidden, setHidden] = useState(true);
	const [checkboxValue, setCheckboxValue] = useState(Array<any>);

	function getMajorIds() {
		const majorIds: any = [];
		checkboxValue.forEach((item: any, index: number) => {
			majorIds.push(props.json.find((e: any) => e.name === item).id);
		});
		return majorIds;
	}

	const post = () => {
		if (!name || !codename || !checkboxValue) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = "http://localhost:3010/courses";
		//const course_id = props.json.find((e: any) => e.name === selected).id;
		const major_ids = getMajorIds();

		//console.log("posting to: " + url);
		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				//token: token,
				course: {
					name: name,
					codename: codename,
					major_ids: major_ids,
					token: token,
				},
			}),
			method: "POST",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	// Add/Remove checked item from list
	const handleCheck = (event: any) => {
		var updatedList = [...checkboxValue];
		if (event.target.checked) {
			updatedList = [...checkboxValue, event.target.value];
		} else {
			updatedList.splice(checkboxValue.indexOf(event.target.value), 1);
		}
		setCheckboxValue(updatedList);
		//console.log(checkboxValue);
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		if (props.json && checkboxValue.length === 0) {
			//const array:Array<boolean> = Array(props.majorNames.length).fill(false)
			//setCheckboxValue(array)
		}
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Nova Disciplina
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Código</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="CI0000"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setCodename(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Cursos Atrelados</label>
							{props.majorNamesPlain.map(
								(item: any, index: number) => (
									<label
										key={
											"checkboxMajorsInNewCourse" +
											index.toString()
										}
										className="checkbox"
									>
										<div>
											<input
												value={item}
												type="checkbox"
												onChange={handleCheck}
											></input>
											<span>
												&nbsp;{item}&nbsp;&nbsp;&nbsp;
											</span>
										</div>
									</label>
								)
							)}
						</div>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={post}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Nova Disciplina</a>
		</div>
	);
}

export function EditCourse(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [checkbox, setCheckbox] = useState([]);
	const [isLoading, setLoading] = useState("");
	const [selectedCourse, setSelectedCourse] = useState("");
	const [isHidden, setHidden] = useState(true);
	const [name, setName] = useState("");
	const [codename, setCodename] = useState("");
	const [checkboxValue, setCheckboxValue] = useState(Array<any>);
	const [previousCourses, setPreviousCourses] = useState([]);

	function getMajorIds() {
		const majorIds: any = [];
		//console.log(props.json);
		checkboxValue.forEach((item: any, index: number) => {
			majorIds.push(
				props.jsonMajors.find((e: any) => e.name === item).id
			);
		});
		return majorIds;
	}

	function student_url() {
		//const [student_name, course_name] = selectedStudent.split(" - ");
		const course = props.json.find((e: any) => e.name === selectedCourse);
		//const student = course.students.find(
		//	(e: any) => e.name === student_name
		//);
		console.log(course);
		return "http://localhost:3010/courses/" + course.id.toString();
	}

	const put = () => {
		/*
		console.log(name);
		console.log(codename);
		console.log(selectedCourse);
		*/

		if (!selectedCourse) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = student_url();
		const course_id = () => {
			if (selectedCourse) {
				if (selectedCourse === "Não Alterar") return null;
				const course = props.json.find(
					(e: any) => e.name === selectedCourse
				);
				return course.id;
			} else return null;
		};

		/*
		console.log("posting to: " + url);
		console.log(token);
		console.log(course_id());
		console.log(checkboxValue);
		console.log(getMajorIds());
		*/

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
				course: {
					name: name,
					codename: codename,
					major_ids: getMajorIds(),
				},
			}),
			method: "PUT",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	// Add/Remove checked item from list
	const handleCheck = (event: any) => {
		var updatedList = [...checkboxValue];
		if (event.target.checked) {
			updatedList = [...checkboxValue, event.target.value];
		} else {
			updatedList.splice(checkboxValue.indexOf(event.target.value), 1);
		}
		setCheckboxValue(updatedList);
		//console.log(checkboxValue);
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const handleChange = (e: any) => {
		setSelectedCourse(e.target.value);
		//setCheckbox([]);
		const course = props.json.find((elem: any) => {
			return elem.name === e.target.value;
		});
		const majors = course.majors.map((e: any) => e.name);
		//console.log(majors);
		const majorsObj: any = [];
		//allmajors.forEach((elem: any) => {});
		//console.log(majors);
		//console.log(props.courseNames);

		const checkboxTemp: any = [];
		props.majorNamesPlain.forEach((item: any, index: number) => {
			if (majors.includes(item)) {
				//console.log("INCLUDES");
				checkboxTemp.push(" |" + item + "| ");
				//const elem = document.getElementById(
				//	"checkboxEditCourse" + index.toString()
				//) as HTMLInputElement;
				//elem.checked = true;
				/*
				checkboxTemp.push(
					<label
						key={"checkboxEditCourse" + index.toString()}
						className="checkbox"
					>
						<div>
							<input type="checkbox" defaultChecked={true}></input>
							&nbsp;{item}&nbsp;&nbsp;&nbsp;
						</div>
					</label>
				);
				*/
			} else {
				//const elem = document.getElementById(
				//	"checkboxEditCourse" + index.toString()
				//) as HTMLInputElement;
				//elem.checked = false;
				/*
				checkboxTemp.push(
					<label
						key={"checkboxEditCourse" + index.toString()}
						className="checkbox"
					>
						<div>
							<input type="checkbox"></input>
							&nbsp;{item}&nbsp;&nbsp;&nbsp;
						</div>
					</label>
				);
				*/
			}
		});
		setPreviousCourses(checkboxTemp);
		//console.log(checkboxTemp);
		//setCheckbox(checkboxTemp);
		//console.log("checkbox SET");
		//console.log("================");
		//console.log(checkbox);
		//console.log("================");

		//console.log(props.courseNames[0].props.children.props.children);
	};

	const active = isModal ? "is-active" : "";

	useEffect(() => {
		//console.log("updating checkbox");
	}, [checkbox]);

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		if (props.json[0]) {
			const course = props.json[0];
			const majors = course.majors.map((e: any) => e.name);
			//console.log(majors);
			const checkboxTemp: any = [];
			const previous: any = [];
			props.majorNamesPlain.forEach((item: any, index: number) => {
				if (majors.includes(item)) {
					previous.push(" |" + item + "| ");
					//console.log("INCLUDES");
					checkboxTemp.push(
						<label
							key={
								"checkboxEditCourse" +
								(
									index * props.majorNamesPlain.length
								).toString()
							}
							className="checkbox"
						>
							<div>
								<input
									type="checkbox"
									id={"checkboxEditCourse" + index.toString()}
									defaultChecked={true}
								></input>
								&nbsp;{item}&nbsp;&nbsp;&nbsp;
							</div>
						</label>
					);
				} else
					checkboxTemp.push(
						<label
							key={
								"checkboxEditCourse" +
								(
									index * props.majorNamesPlain.length
								).toString()
							}
							className="checkbox"
						>
							<div>
								<input
									type="checkbox"
									id={"checkboxEditCourse" + index.toString()}
								></input>
								&nbsp;{item}&nbsp;&nbsp;&nbsp;
							</div>
						</label>
					);
			});
			//setPreviousCourses(previous);
			setCheckbox(checkboxTemp);
		}
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, [props.json, props.majorNamesPlain]);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Editar Disciplina
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Disciplina</label>
							<div className="control">
								<div className="select">
									<select
										onChange={handleChange}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.courseNames}
									</select>
								</div>
							</div>
						</div>
						<div className="field">
							<label className="label">Novo Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Novo Código</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="CI0000"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setCodename(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Cursos Atrelados</label>
							{props.majorNamesPlain.map(
								(item: any, index: number) => (
									<label
										key={
											"checkboxMajorsInNewCourse" +
											index.toString()
										}
										className="checkbox"
									>
										<div>
											<input
												value={item}
												type="checkbox"
												onChange={handleCheck}
											></input>
											<span>
												&nbsp;{item}&nbsp;&nbsp;&nbsp;
											</span>
										</div>
									</label>
								)
							)}
						</div>
						<em>Atualmente atrelados:</em>
						<div></div>
						<em>{previousCourses}</em>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={put}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Editar Disciplina</a>
		</div>
	);
}

export function RemoveCourse(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [isLoading, setLoading] = useState("");
	const [selected, setSelected] = useState("");
	const [isHidden, setHidden] = useState(true);

	function course_url() {
		const course = props.json.find((e: any) => e.name === selected);
		return "http://localhost:3010/courses/" + course.id.toString();
	}

	const postDelete = () => {
		if (!selected) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = course_url();
		console.log("deleting from: " + url);

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
			}),
			method: "DELETE",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Remover Disciplina
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Disciplina</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelected(e.target.value);
										}}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.courseNames}
									</select>
								</div>
							</div>
						</div>

						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={postDelete}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Remover Disciplina</a>
		</div>
	);
}

export function NewMajor(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [name, setName] = useState("");
	//const [codename, setCodename] = useState("");
	const [selected, setSelected] = useState("");
	const [isLoading, setLoading] = useState("");
	const [isHidden, setHidden] = useState(true);
	const [checkboxValue, setCheckboxValue] = useState(Array<any>);

	function getCourseIds() {
		const courseIds: any = [];
		checkboxValue.forEach((item: any, index: number) => {
			courseIds.push(props.json.find((e: any) => e.name === item).id);
		});
		return courseIds;
	}

	const post = () => {
		/*
		console.log(name);
		console.log(checkboxValue);
		console.log();
		console.log();
		*/

		if (!name || !checkboxValue) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = "http://localhost:3010/majors";
		//const course_id = props.json.find((e: any) => e.name === selected).id;
		const course_ids = getCourseIds();

		/*
		console.log(url);
		console.log(token);
		console.log(name);
		console.log(course_ids);
		*/

		//console.log("posting to: " + url);
		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
				major: {
					name: name,
					course_ids: course_ids,
				},
			}),
			method: "POST",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	// Add/Remove checked item from list
	const handleCheck = (event: any) => {
		var updatedList = [...checkboxValue];
		if (event.target.checked) {
			updatedList = [...checkboxValue, event.target.value];
		} else {
			updatedList.splice(checkboxValue.indexOf(event.target.value), 1);
		}
		setCheckboxValue(updatedList);
		//console.log(checkboxValue);
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Novo Curso
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">
								Disciplinas Atreladas
							</label>
							{props.courseNamesPlain.map(
								(item: any, index: number) => (
									<label
										key={
											"checkboxCourseInNewMajor" +
											index.toString()
										}
										className="checkbox"
									>
										<div>
											<input
												value={item}
												type="checkbox"
												onChange={handleCheck}
											></input>
											<span>
												&nbsp;{item}&nbsp;&nbsp;&nbsp;
											</span>
										</div>
									</label>
								)
							)}
						</div>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={post}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Novo Curso</a>
		</div>
	);
}

export function EditMajor(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [checkbox, setCheckbox] = useState([]);
	const [isLoading, setLoading] = useState("");
	const [selectedMajor, setSelectedMajor] = useState("");
	const [isHidden, setHidden] = useState(true);
	const [name, setName] = useState("");
	const [codename, setCodename] = useState("");
	const [checkboxValue, setCheckboxValue] = useState(Array<any>);
	const [previousCourses, setPreviousMajors] = useState([]);

	function getCourseIds() {
		const courseIds: any = [];
		//console.log(props.json);
		checkboxValue.forEach((item: any, index: number) => {
			courseIds.push(
				props.jsonCourses.find((e: any) => e.name === item).id
			);
		});
		return courseIds;
	}

	function student_url() {
		//const [student_name, course_name] = selectedStudent.split(" - ");
		const major = props.json.find((e: any) => e.name === selectedMajor);
		//const student = course.students.find(
		//	(e: any) => e.name === student_name
		//);
		console.log(major);
		return "http://localhost:3010/majors/" + major.id.toString();
	}

	const put = () => {
		console.log(name);
		console.log(selectedMajor);

		if (!selectedMajor) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = student_url();
		const course_id = () => {
			if (selectedMajor) {
				if (selectedMajor === "Não Alterar") return null;
				const course = props.json.find(
					(e: any) => e.name === selectedMajor
				);
				return course.id;
			} else return null;
		};

		console.log("posting to: " + url);
		console.log(token);
		console.log(course_id());
		console.log(checkboxValue);
		console.log(getCourseIds());

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				Referer: "http://localhost:3000/students",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
				major: {
					name: name,
					course_ids: getCourseIds(),
				},
			}),
			method: "PUT",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	// Add/Remove checked item from list
	const handleCheck = (event: any) => {
		var updatedList = [...checkboxValue];
		if (event.target.checked) {
			updatedList = [...checkboxValue, event.target.value];
		} else {
			updatedList.splice(checkboxValue.indexOf(event.target.value), 1);
		}
		setCheckboxValue(updatedList);
		//console.log(checkboxValue);
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	//let checkbox: any;

	const handleChange = (e: any) => {
		setSelectedMajor(e.target.value);

		const major = props.json.find((elem: any) => {
			return elem.name === e.target.value;
		});
		const courses = major.courses.map((e: any) => e.name);

		const checkboxTemp: any = [];
		props.courseNamesPlain.forEach((item: any, index: number) => {
			if (courses.includes(item)) checkboxTemp.push(" |" + item + "| ");
		});
		setPreviousMajors(checkboxTemp);
	};

	const active = isModal ? "is-active" : "";

	useEffect(() => {}, [checkbox]);

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		if (props.json[0] && checkbox.length === 0) {
			const major = props.json[0];
			const courses = major.courses.map((e: any) => e.name);
			const checkboxTemp: any = [];
			props.courseNamesPlain.forEach((item: any, index: number) => {
				if (courses.includes(item)) {
					//console.log("INCLUDES");
					checkboxTemp.push(
						<label
							key={
								"checkboxUpdate" +
								(
									index * props.courseNamesPlain.length
								).toString()
							}
							className="checkbox"
						>
							<div>
								<input
									type="checkbox"
									id={"checkboxEditMajor" + index.toString()}
									defaultChecked
								></input>
								&nbsp;{item}&nbsp;&nbsp;&nbsp;
							</div>
						</label>
					);
				} else
					checkboxTemp.push(
						<label
							key={
								"checkboxUpdate" +
								(
									index * props.courseNamesPlain.length
								).toString()
							}
							className="checkbox"
						>
							<div>
								<input
									type="checkbox"
									id={"checkboxEditMajor" + index.toString()}
								></input>
								&nbsp;{item}&nbsp;&nbsp;&nbsp;
							</div>
						</label>
					);
			});
			setCheckbox(checkboxTemp);
		}

		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, [props.json, props.courseNamesPlain]);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Editar Curso
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Curso</label>
							<div className="control">
								<div className="select">
									<select
										onChange={handleChange}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.majorNames}
									</select>
								</div>
							</div>
						</div>
						<div className="field">
							<label className="label">Novo Nome</label>
							<div className="control">
								<input
									className="input"
									type="text"
									placeholder="Nome"
									onInput={(
										e: React.ChangeEvent<HTMLInputElement>
									) => {
										setName(e.target.value);
									}}
								></input>
							</div>
						</div>
						<div className="field">
							<label className="label">Cursos Atrelados</label>
							{props.courseNamesPlain.map(
								(item: any, index: number) => (
									<label
										key={
											"checkboxMajorsInNewCourse" +
											index.toString()
										}
										className="checkbox"
									>
										<div>
											<input
												value={item}
												type="checkbox"
												onChange={handleCheck}
											></input>
											<span>
												&nbsp;{item}&nbsp;&nbsp;&nbsp;
											</span>
										</div>
									</label>
								)
							)}
						</div>
						<em>Atualmente atrelados:</em>
						<div></div>
						<em>{previousCourses}</em>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={put}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Editar Curso</a>
		</div>
	);
}

export function RemoveMajor(props: any) {
	//Para mais informações, ver como o as classes funcionam no site do Bulma,
	//principalmente a classe "Modal".

	const [isModal, setModal] = useState(false);
	const [isLoading, setLoading] = useState("");
	const [selected, setSelected] = useState("");
	const [isHidden, setHidden] = useState(true);

	function course_url() {
		const major = props.json.find((e: any) => e.name === selected);
		return "http://localhost:3010/majors/" + major.id.toString();
	}

	const postDelete = () => {
		if (!selected) return;
		setLoading(" is-loading");
		const token = getCurrentUser();
		const url = course_url();
		console.log("deleting from: " + url);

		fetch(url, {
			headers: {
				accept: "text/html, application/xhtml+xml, application/json",
				"Referrer-Policy": "strict-origin-when-cross-origin",
				"Content-type": "application/json",
			},
			//body: JSON.stringify({ student: { name: "Æðelwulf", course_id: "1" } }),
			body: JSON.stringify({
				token: token,
			}),
			method: "DELETE",
		}).then((response) => {
			//console.log(response.ok);
			if (response.ok) window.location.reload();
			else {
				setHidden(false);
				setLoading("");
				throw new Error("Status code error");
			}
		});
	};

	//Ao clicar no box, definir o modal como ativo.
	const handleModalOpen = () => {
		setModal(true);
	};

	//Ao clicar no 'x', ou fora do modal definir o modal como inativo.
	const handleModalClose = () => {
		setModal(false);
	};

	function closeModal() {
		setModal(false);
	}

	const active = isModal ? "is-active" : "";

	//Permite fechar o modal apertando ESC.
	useEffect(() => {
		const handleEsc = (event: KeyboardEvent) => {
			if (event.key === "Escape") {
				setModal(false);
			}
		};
		window.addEventListener("keydown", handleEsc);

		return () => {
			window.removeEventListener("keydown", handleEsc);
		};
	}, []);

	return (
		<div className="Modal">
			<div className={`modal ${active}`}>
				{/*O handleClick abaixo serve para permitir que o modal
				possa ser fechado ao clicar fora dele.*/}
				<div className="modal-background" onClick={handleModalClose} />
				<div className="modal-card is-center-aligned">
					<header
						className="modal-card-head"
						style={{ backgroundColor: "#edfcee" }}
					>
						<p
							className="modal-card-title"
							style={{
								whiteSpace: "pre-line",
							}}
						>
							Remover Curso
						</p>
						<button
							onClick={handleModalClose}
							className="delete"
							aria-label="close"
						/>
					</header>
					<section className="modal-card-body is-left-aligned">
						<div className="field">
							<label className="label">Curso</label>
							<div className="control">
								<div className="select">
									<select
										onChange={(e) => {
											setSelected(e.target.value);
										}}
										defaultValue={"selecione"}
									>
										<option
											value="selecione"
											disabled
											hidden
										>
											Selecione
										</option>
										{props.majorNames}
									</select>
								</div>
							</div>
						</div>
						<div
							className="has-text-centered"
							style={{ backgroundColor: "red", color: "white" }}
							hidden={isHidden}
						>
							Erro Desconhecido
						</div>
						<div>&nbsp;</div>
						<div className="field is-grouped has-addons has-addons-centered">
							<div className="control">
								<button
									className={"button is-link" + isLoading}
									onClick={postDelete}
								>
									Confirmar
								</button>
							</div>
							<div className="control">
								<button
									className="button is-link is-light"
									onClick={handleModalClose}
								>
									Cancelar
								</button>
							</div>
						</div>
					</section>
					<footer
						className="modal-card-foot"
						style={{ backgroundColor: "#edfcee" }}
					></footer>
				</div>
			</div>
			<a onClick={handleModalOpen}>Remover Curso</a>
		</div>
	);
}
