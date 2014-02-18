package org.yafra.orm;

import org.yafra.orm.auto._OrgYafraYafraMap;

public class OrgYafraYafraMap extends _OrgYafraYafraMap {

    private static OrgYafraYafraMap instance;

    private OrgYafraYafraMap() {}

    public static OrgYafraYafraMap getInstance() {
        if(instance == null) {
            instance = new OrgYafraYafraMap();
        }

        return instance;
    }
}
