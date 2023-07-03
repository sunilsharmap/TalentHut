Reference:
---------------------------------------------------------------------------------------------------
	https://gerrit.googlesource.com/git-repo/+/master/docs/manifest-format.md#Element-remote
	https://www.instructables.com/id/Using-Googles-repo-command-in-your-own-projects/

---------------------------------------------------------------------------------------------------

`proj-1` and `proj-2` - Separate git repositories.

`Project_Main_repo.git` - Git repository for whole project, it contains the manifest files for respective repositories.
		It has 3 files: 1. default.xml    --  For both Project-1 and Project-2
                        2. project-1.xml  --  Only Project-1
                        3. project-1.xml  --  Only Project-2
---------------------------------------------------------------------------------------------------

How to create `Project_Main_repo.git` Repository:

	mkdir Project_Main_repo.git
    git init
	create .xml files

Give the proper `fetch` url<file location> to clone the repo
---------------------------------------------------------------------------------------------------

How to use repo command for multiple git repositories for project:

create a directory to initialize the repo
	mkdir source_code

Initialize the repo:
	Whole repo of the project:
		repo init -u <url of the Project_Main_repo.git>
		if `Project_Main_repo.git` is located in home then `repo init /home/USER_NAME/Project_Main_repo.git`

	Only Project-1 source:
		repo init -u <url of the Project_Main_repo.git> -m <corresponding .xml>
		ex: repo init /home/USER_NAME/Project_Main_repo.git -m project-1.xml

	Only Project-2 source:
		repo init -u <url of the Project_Main_repo.git> -m <corresponding .xml>
		ex: repo init /home/USER_NAME/Project_Main_repo.git -m project-2.xml
---------------------------------------------------------------------------------------------------
