# install-root-geant4.sh
# Hernán Asorey <asoreyh@gmail.com> 
# A simple script for installing root and Geant4 in a modern release of the ubuntu OS. 
# It is provided as is. Please notice it will modify your ${USER}/.bashrc file.
# If you find this useful, please acknowledge. 

# Instructions: 
# You should change only the following three environment variables below
# root version
root_version="6.28.04"
# Geant4 version 
g4_src="10.07.p04"
# and the work directory (where root and Geant4 will be installed). 
wdir=${HOME}/work

# You should not need to change anything below for standard installation

# install required dependencies
sudo apt-get -y update && sudo apt-get -y dist-upgrade
sudo apt-get -y install vim screen wget git curl rsync gnu-standards build-essential dpkg-dev g++ gcc binutils libx11-dev libxpm-dev libxft-dev libxext-dev libssl-dev gfortran libpcre3-dev xlibmesa-glu-dev libglew-dev libftgl-dev libmysqlclient-dev libfftw3-dev libcfitsio-dev graphviz-dev libavahi-compat-libdnssd-dev libldap2-dev libxml2-dev libkrb5-dev libgsl0-dev qtwebengine5-dev cmake cmake-curses-gui python3 python3-dev libboost-all-dev nlohmann-json3-dev ca-certificates libz-dev libzstd-dev libxerces-c-dev nlohmann-json3-dev python3-pygccxml libxmu-dev libqt5webkit5 libqt5webkit5-dev libqt5webview5 libqt5webview5-dev libqt53dcore5 libqt53dextras5 libqt53dinput5 libqt53drender5 libqt53dquickrender5 libqt53dquickinput5 libqt5x11extras5 libqt5x11extras5-dev libqt5gui5
start=$(date)

# create the work directory at user's ${HOME} and get the number of procs
[ ! -d ${wdir} ] && mkdir ${wdir}
echo "wdir=${wdir}" >> ${HOME}/.bashrc
nproc=$(( $(nproc) / 2))


# check for root, if it is installed, continue with geant4
hasroot=0
source $wdir/$dir/${root_version}-install/bin/thisroot.sh
if root -q > /dev/null; then 
	echo "root is installed. We can continue"
	hasroot=1
else 
	echo "root is not installed. Let's install it"
fi

# downloading and unpacking root
if !$root; then
target=root
dir=ROOT
mkdir $wdir/$dir
cd $wdir/$dir
wget -c https://root.cern.ch/download/root_v${root_version}.source.tar.gz
tar xvfz ${target}_v${root_version}.source.tar.gz
rm -v ${target}_v${root_version}.source.tar.gz
mv root-${root_version} ${root_version}
mkdir ${root_version}-build ${root_version}-install
cd ${root_version}-build

cmake ../${root_version} && cmake --build . -- -j ${nproc} && cmake --build . -- -j ${nproc} && cmake -DCMAKE_INSTALL_PREFIX=$wdir/$dir/${root_version}-install/  -P  cmake_install.cmake 

# check if root is correctly installed
source $wdir/$dir/${root_version}-install/bin/thisroot.sh
if root -q > /dev/null; then 
	echo "root is installed. We can continue"
else 
	echo "root installation failed. please check the log and try again"
	exit 99;
fi

now=$(date)
echo "
#
## Added by install.sh tool on ${now}
### ROOT
export ROOT_VERSION=${root_version}
export ROOT_BASE=\${wdir}/ROOT/\${ROOT_VERSION}-install
source \${ROOT_BASE}/bin/thisroot.sh
###
##
#
" >> ${HOME}/.bashrc
source ${HOME}/.bashrc
fi

# installing geant4
g4_src="10.07.p04"
g4_version="${g4_src}"
g4_dir="GEANT4"
g4_install="${wdir}/${g4_dir}/${g4_version}-install"
g4_data="${g4_install}/share/Geant4-${g4_version}/data"
mkdir $wdir/$g4_dir
cd $wdir/$g4_dir 
wget -c https://cern.ch/geant4-data/releases/geant4.${g4_src}.tar.gz
tar xvfz geant4.${g4_src}.tar.gz
rm -v geant4.${g4_src}.tar.gz
mv geant4.${g4_src} ${g4_version}
mkdir ${g4_version}-build ${g4_version}-install
cd ${g4_version}-build
cmake \
	-DCMAKE_INSTALL_PREFIX=${g4_install} \
	-DGEANT4_INSTALL_DATA=ON \
	-DGEANT4_INSTALL_DATADIR=${g4_data} \
	-DGEANT4_USE_OPENGL_X11=ON \
	-DGEANT4_USE_PYTHON=ON \
	-DGEANT4_USE_QT=ON \
	-DGEANT4_USE_RAYTRACER_X11=ON \
	-DGEANT4_USE_SYSTEM_EXPAT=ON \
	${wdir}/${g4_dir}/${g4_version} \
	&& make -j ${nproc} \
	&& make -j ${nproc} \
	&& make install
cd ${g4_data}
wget -c ftp://gdo-nuclear.ucllnl.org/LEND_GND1.3/LEND_GND1.3_ENDF.BVII.1.tar.gz
tar xfv LEND_GND1.3_ENDF.BVII.1.tar.gz
rm LEND_GND1.3_ENDF.BVII.1.tar.gz
libs=$(cat ${g4_install}/bin/geant4.sh | grep "export G4")
libs="${libs} export G4LENDDATA=\"${wdir}/${g4_dir}/${g4_install}/share/${datadir}/data/LEND_GND1.3_ENDF.BVII.1\""

source ${g4_install}/bin/geant4.sh 2> /dev/null
if geant4-config --prefix > /dev/null 2> /dev/null; then 
	echo "geant4 is installed. We can continue"; 
else 
	echo "geant4 installation failed. Please check the log and try again";
	exit 99;
fi

now=$(date)
echo "#" >> ${HOME}/.bashrc
echo "## Added by install.sh tool on ${now}" >> ${HOME}/.bashrc
echo "### GEANT4" >> ${HOME}/.bashrc
echo "wdir=${wdir}" >> ${HOME}/.bashrc
echo "geant4_base=${wdir}/${g4_dir}" >> ${HOME}/.bashrc
echo "geant4_version=${g4_version}" >> ${HOME}/.bashrc
echo "geant4_code=Geant4-\${geant4_version}" >> ${HOME}/.bashrc
echo "geant4_path=\${geant4_base}/\${geant4_version}-install" >> ${HOME}/.bashrc
echo "geant4_build=\${geant4_path}/lib/\${geant4_code}/" >> ${HOME}/.bashrc
echo "source \${geant4_path}/bin/geant4.sh" >> ${HOME}/.bashrc
echo "export geant4_data=\${geant4_path}/share/\${geant4_code}/data" >> ${HOME}/.bashrc
echo "export geant4_examples=\${geant4_path}/share/\${geant4_code}/examples" >> ${HOME}/.bashrc
echo "# Geant4 Libraries" >> ${HOME}/.bashrc
for i in $(echo $libs | sed -e 's/export //g'); do echo "export $i" >> ${HOME}/.bashrc; done
echo "###" >> ${HOME}/.bashrc
echo "##" >> ${HOME}/.bashrc
echo "#" >> ${HOME}/.bashrc
source ${HOME}/.bashrc
cd ${HOME}
end=$(date)
echo "Done. Start: $start // End: $end"
