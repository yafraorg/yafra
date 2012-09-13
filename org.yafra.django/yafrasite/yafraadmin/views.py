# Create your views here.
from django.http import HttpResponse
from yafrasite.yafraadmin.models import Yafrauser

def index(request):
    yu = Yafrauser.objects.all()
    output='List of yafra users:<p /><div id="usertable"><table border="1"><tr><th>Username</th></tr>'
    for i in yu:
        record='<tr><td>' +i.name + '</td></tr>'
        output = output + record
    output + '</table></div>'
    return HttpResponse(output)
