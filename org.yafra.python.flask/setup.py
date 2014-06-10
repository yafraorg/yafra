from setuptools import setup


setup(name='YafraPython',
      version='1.0',
      description='OpenShift Yafra Python App',
      author='Yafra Admin',
      author_email='yafraorg@gmail.com',
      url='http://www.python.org/sigs/distutils-sig/',
      install_requires=['Flask>=0.10', 'xlwt>=0.7.5', 'reportlab>=3.0', 'MarkupSafe>=0.18', 'Werkzeug>=0.9.4',
                        'Flask-SQLAlchemy>=1.0', 'Jinja2>=2.7.2', 'SQLAlchemy>=0.9.3', 'Pillow>=2.4.0',
                        'Flask-Mail>=0.9.0'],
)
