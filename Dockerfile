FROM ubuntu:22.04

ENV user cose-354

RUN apt-get update
RUN apt-get -y install gcc gdb gcc-multilib git vim python3-pip gdbserver netcat
RUN python3 -m pip install --upgrade pip
RUN python3 -m pip install --upgrade pwntools

RUN adduser $user

ADD ./Stage1_Mallory/. /home/$user/Stage1_Mallory/
ADD ./Stage2_Trent/. /home/$user/Stage2_Trent/
ADD ./Stage3_Mallory/. /home/$user/Stage3_Mallory/
ADD ./Stage4_Trent/. /home/$user/Stage4_Trent/
ADD ./Stage5_Trent/. /home/$user/Stage5_Trent/
ADD ./Stage6_Trent/. /home/$user/Stage6_Trent/

WORKDIR /home/$user/

RUN chmod 770 /home/$user/
RUN chmod 770 /home/$user/*/
RUN chmod 770 /home/$user/*/*.o
RUN chmod 770 /home/$user/*/*.so.6
RUN chmod 660 /home/$user/*/*.c
RUN chmod 660 /home/$user/*/*.py
RUN chmod 660 /home/$user/*/*.txt

RUN chown -R $user:$user /home/$user/*

USER $user

RUN git clone https://github.com/longld/peda.git /tmp/peda
RUN echo "source /tmp/peda/peda.py" >> ~/.gdbinit
RUN echo "DONE! debug your program with gdb and enjoy"

WORKDIR /home/$user