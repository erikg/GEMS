Summary: A modular MUA.
Name: gems
Version: 0.0
Release: 1
Copyright: GPL
Vendor: Erik Greenwald
Url: http://math.smsu.edu/~br0ke/gems.html
Group: Applications/Mail
Source0: http://math.smsu.edu/~br0ke/files/gems-0.0.tar.gz
Buildroot: /var/tmp/gems

%description
kickass MUA

%prep
%setup -q
%build
CFLAGS="$RPM_OPT_FLAGS" ./configure --prefix=/usr

make

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
/usr/*

%changelog

