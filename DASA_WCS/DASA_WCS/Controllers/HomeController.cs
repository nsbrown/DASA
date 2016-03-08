using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace DASA_WCS.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            ViewBag.Message = "Home Menu Page";
            return View();
        }

        public ActionResult Profiles()
        {
            ViewBag.Message = "Profile Selector Page";

            return View();
        }

        public ActionResult mProfiles()
        {
            ViewBag.Message = "Profile Manager Page";

            return View();
        }

        public ActionResult mShower()
        {
            ViewBag.Message = "Shower Management Page";
            return View();
        }
    }
}