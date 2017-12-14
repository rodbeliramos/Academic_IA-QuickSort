<h1>Contribuidores do projeto</h1>

Todas as contribuições deste projeto, tanto da parte estrutural quanto da parte funcional foram planejadas e discutidas em equipe. Muitas vezes, ambos os contribuidores tiveram de alterar o código implementado pelo o outro.

<p><h3>Rafael Fernando Reis</h3>
Graduando em Engenharia Eletrônica</br>
<a href="mailto:reis.rafael.fernando@gmail.com">reis.rafael.fernando@gmail.com</a></br>
<b>Responsável pela parte funcional do projeto</b>
</p>

<h4>Implementado:</h4>

	- main.c -- implementação da interface com o usuário.
		- menu
	- matriz_curricular.c -- implementação das funções para carregar e salvar os dados referentes as matrizes curriculares.
		- file functions
			mc_node_load_mc()
			mc_node_save_mc()
	- aluno.c -- implementação das funções para carregar e salvar os dados dos alunos.
		- file functions
			aluno_load_from_txt()
			aluno_save_to_csv()
			aluno_load_from_csv()
	 - ordenacao.c -- implementação das funções de ordenação, atualmente somente a ordenação por quicksort foi implementada.
		- functions:
			ordernar_quicksort()
			mediana_de_tres()
			swap_alunos()
			quicksort()
			particionar()

<p><h3>Rodrigo Belisário Ramos</h3>
Tecnólogo em Sistemas Eletrônicos e Graduando em Engenharia Eletrônica.</br>
<a href="mailto:rodbelisario@gmail.com">rodbelisario@gmail.com</a></br>
<b>Resposável pela parte estrutural do projeto</b>
</p>

<h4>Implementado:</h4>

	- node.c -- modificação do arquivo no.c apresentado em sala de aula para funcionar em lista duplamente encadeada.
		- funtions:
			node_delete()
		- getters methods:
			node_get_previous()

	- doubly_linked_list.c -- modificação do arquivo lista_enc.c apresentado em sala de aula para funcionar como lista duplamente encadeada.
		- functions:
			dll_delete()
			dll_add_head()
			dll_remove_between()
			dll_take_node_at_pos()
	 	- getters methods:
			dll_get_tail()
			dll_get_list_size()
	
	- unidade_curricular.c -- implementação da estrutura e as funções referentes às unidades curriculares das matrizes curriculares.
		- functions:
			uc_node_new()
			uc_node_delete()
		- print functions:
			uc_node_print()
		- getters methods:
			uc_node_get_semestre()
			uc_node_get_codigo()
			uc_node_get_nome()
			uc_node_get_carga_horaria()
	
	- matriz_curricular.c -- implementação da estrutura e as funções referentes às matrizes curriculares dos cursos.
		- functions:
			mc_node_new()
			mc_node_delete()
		- list functions:
			mc_node_uc_new();
			mc_node_uc_delete()
			mc_node_find_uc_node()
		- print functions
			mc_node_print()
		- getters methods
			mc_node_get_id_grade();
			mc_node_get_nome_curso();
			mc_node_get_id_curso();
			mc_node_get_ano_criacao();
			mc_node_get_semestre_criacao();
			mc_node_get_total_horas();
			mc_node_get_uc_node_list();
			mc_node_get_uc_node_total();
	
	- disciplina.c -- implementação da estrutura e as funções referentes as disciplinas cursadas pelo aluno.
		- functions:
			discip_node_new()
			discip_node_delete()
		- print functions:
			discip_node_print()
		- getters methods:
			discip_node_get_uc_node()
			discip_node_get_turma()
			discip_node_get_conceito()
			discip_node_get_faltas()
			discip_node_get_frequencia()
			discip_node_get_origem()
			discip_node_get_situacao()
	
	- aluno.c -- Implementação da estrutura e as funções referentes aos alunos.
		- functions:
			aluno_new()
			aluno_delete()
		- list functions:
			aluno_discip_new()
			aluno_find_mc_node()
 		- print functions
			aluno_print()
		- getters methods:
			aluno_get_id_curso()
			aluno_get_id_grade()
			aluno_get_matricula()
			aluno_get_nome()
			aluno_get_ano_entrada()
			aluno_get_semestre_entrada()
			aluno_get_situacao()
			aluno_get_horas_cursadas()
			aluno_get_ia()
			aluno_get_mc_do_curso()
			aluno_get_discip_node_list()
			aluno_get_discip_node_total()




 
