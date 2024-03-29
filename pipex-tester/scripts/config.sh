#!/bin/bash

prompt_configuration()
{
	printf "\t${BOLD}Configuration${NC}\n\n"
	printf "The project directory (default: ../): "
	read project_directory
	if [ -z "$project_directory" ]
	then
		project_directory="../"
	fi
	if [ -z "$project_directory" ]
	then
		project_directory="../"
	fi
	printf "\n"
	printf "Would you like to check for updates on run ?\nThis option is recommended as the tester is still actively updated\n"
	check_update=-1
	while [ $check_update -ne 0 ] && [ $check_update -ne 1 ]
	do
		printf "Check for update on run [Y/n] "
		nchars_opt="-N"
		if [[ "$OSTYPE" == "darwin"* ]]
		then
			nchars_opt="-n"
		fi
		read $nchars_opt 1 -r check_update
		[[ "$check_update" != $'\n' ]] && echo
		case "$check_update" in
			[nN]) check_update=0 ;;
			[yY$'\n']) check_update=1 ;;
		esac
		if [ "$check_update" != "0" ] && [ "$check_update" != "1" ]
		then
			printf "${YELLOW}Unexpected answer. Please retry...${NC}\n"
			check_update=-1
		fi
	done

	if ! touch config.vars > /dev/null 2>&1 && ! [ -w config.vars ]
	then
		printf "${YELLOW}Unable to create the configuration file as your user...${NC}\n"
		PROJECT_DIRECTORY=$project_directory
		CHECK_UPDATE=$check_update
		READ_CONFIG=0
	else
		echo "# This file was automatically generated by the pipex-tester" > config.vars
		echo "# https://github.com/vfurmane/pipex-tester" >> config.vars
		echo >> config.vars
		echo "PROJECT_DIRECTORY='$project_directory'" >> config.vars
		echo "CHECK_UPDATE=$check_update" >> config.vars
	fi
}
