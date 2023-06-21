FROM asoreyh/root
LABEL maintainer.name="Hernán Asorey"
LABEL maintainer.email="asoreyh@gmail.com"
ENV LANG=C.UTF-8
ENV wdir="/opt"
# basics
WORKDIR ${wdir}

# geant4 env
ARG g4_src="10.07.p04"
ARG g4_version="${g4_src}"
ARG g4_dir="GEANT4"
ARG g4_install="${wdir}/${g4_dir}/${g4_version}-install"
ARG g4_data="${g4_install}/share/Geant4-${g4_version}/data"

RUN apt-get -y update \
 && apt-get -y dist-upgrade \
 && mkdir $wdir/$g4_dir \
 && cd $wdir/$g4_dir  \
 && wget -c https://cern.ch/geant4-data/releases/geant4.${g4_src}.tar.gz \
 && tar xvfz geant4.${g4_src}.tar.gz \
&& rm -v geant4.${g4_src}.tar.gz \
 && mv geant4.${g4_src} ${g4_version} \
 && mkdir ${g4_version}-build ${g4_version}-install \
 && cd ${g4_version}-build \
 && cmake \
      -DCMAKE_INSTALL_PREFIX=${g4_install} \
      -DGEANT4_INSTALL_DATA=ON \
      -DGEANT4_INSTALL_DATADIR=${g4_data} \
	  -DGEANT4_USE_OPENGL_X11=ON \
	  -DGEANT4_USE_PYTHON=ON \
	  -DGEANT4_USE_QT=ON \
	  -DGEANT4_USE_RAYTRACER_X11=ON \
	  -DGEANT4_USE_SYSTEM_EXPAT=ON \
      ${wdir}/${g4_dir}/${g4_version} \
 && make -j4 \
 && make -j4 \
 && make install \
 && libs=$(cat ${g4_install}/bin/geant4.sh | grep "export G4") \
 && cd ${g4_data} \
 && wget -c ftp://gdo-nuclear.ucllnl.org/LEND_GND1.3/LEND_GND1.3_ENDF.BVII.1.tar.gz \
 && tar xfv LEND_GND1.3_ENDF.BVII.1.tar.gz \
 && rm LEND_GND1.3_ENDF.BVII.1.tar.gz \
 && libs="${libs} export G4LENDDATA=\"${wdir}/${g4_dir}/${g4_install}/share/${datadir}/data/LEND_GND1.3_ENDF.BVII.1\"" \
 && now=$(date) \
 && echo "#" >> ${HOME}/.bashrc \
 && echo "## Added by install.sh tool on ${now}" >> ${HOME}/.bashrc \
 && echo "### GEANT4" >> ${HOME}/.bashrc \
 && echo "wdir=${wdir}" >> ${HOME}/.bashrc \
 && echo "geant4_base=${wdir}/${g4_dir}" >> ${HOME}/.bashrc \
 && echo "geant4_version=${g4_version}" >> ${HOME}/.bashrc \
 && echo "geant4_code=Geant4-\${geant4_version}" >> ${HOME}/.bashrc \
 && echo "geant4_path=\${geant4_base}/\${geant4_version}-install" >> ${HOME}/.bashrc \
 && echo "geant4_build=\${geant4_path}/lib/\${geant4_code}/" >> ${HOME}/.bashrc \
 && echo "source \${geant4_path}/bin/geant4.sh" >> ${HOME}/.bashrc \
 && echo "export geant4_data=\${geant4_path}/share/\${geant4_code}/data" >> ${HOME}/.bashrc \
 && echo "export geant4_examples=\${geant4_path}/share/\${geant4_code}/examples" >> ${HOME}/.bashrc \
 && echo "# Geant4 Libraries" >> ${HOME}/.bashrc \
 && for i in $(echo $libs | sed -e 's/export //g'); do echo "export $i" >> ${HOME}/.bashrc; done \
 && echo "###" >> ${HOME}/.bashrc \
 && echo "##" >> ${HOME}/.bashrc \
 && echo "#" >> ${HOME}/.bashrc
CMD bash
