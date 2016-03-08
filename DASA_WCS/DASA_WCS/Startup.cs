using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(DASA_WCS.Startup))]
namespace DASA_WCS
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
